
#include"CRCUtil.h"
CRCUtil::CRCUtil(char encryptionKey)
    : crc_table_(256),
    table_generated_(false),
    encryption_key_(encryptionKey) {
    GenerateCrcTable();
}

void CRCUtil::GenerateCrcTable() {
    if (table_generated_) return;

    for (uint32_t i = 0; i < 256; ++i) {
        uint32_t crc = i << 24;
        for (int j = 0; j < 8; ++j) {
            crc = (crc & 0x80000000) ? (crc << 1) ^ 0x04C11DB7 : crc << 1;
        }
        crc_table_[i] = crc;
    }
    table_generated_ = true;
}

uint32_t CRCUtil::CalculateCrc32(const void* data, size_t length) const {
    const uint8_t* bytes = static_cast<const uint8_t*>(data);
    uint32_t crc = 0xFFFFFFFF;

    for (size_t i = 0; i < length; ++i) {
        crc = (crc << 8) ^ crc_table_[((crc >> 24) ^ bytes[i]) & 0xFF];
    }
    return crc ^ 0xFFFFFFFF;
}

void CRCUtil::XorCipher(char* data, size_t length) const
{
    for (size_t i = 0; i < length; ++i) {
        data[i] ^= encryption_key_;
    }
}
void CRCUtil::GenerateChecksum(char* data, size_t len) {
    if (!table_generated_) GenerateCrcTable();

    // 校验数据长度
    if (len < sizeof(HEAD)) {
        throw std::invalid_argument("Data length smaller than HEAD size");
    }

    HEAD* header = reinterpret_cast<HEAD*>(data);
    char* business_data = data + sizeof(HEAD);
    size_t business_len = len - sizeof(HEAD);

    // 加密业务数据后计算CRC
    XorCipher(business_data, business_len);
    uint32_t crc = CalculateCrc32(business_data, business_len);
    snprintf(header->crc32, sizeof(header->crc32), "%08X", crc);
}

bool CRCUtil::ValidateData(const char* data, size_t len) {
    if (!table_generated_) GenerateCrcTable();

    // 校验数据长度
    if (len < sizeof(HEAD)) return false;

    const HEAD* header = reinterpret_cast<const HEAD*>(data);
    char* business_data = const_cast<char*>(data + sizeof(HEAD));
    size_t business_len = len - sizeof(HEAD);

    // 解密并重新加密来验证数据
    XorCipher(business_data, business_len);  // 第一次异或：解密
    XorCipher(business_data, business_len);  // 第二次异或：恢复加密状态

    // 计算校验值
    uint32_t calculated_crc = CalculateCrc32(business_data, business_len);
    char expected_crc[9];
    snprintf(expected_crc, sizeof(expected_crc), "%08X", calculated_crc);

    // 恢复原始加密状态（第三次异或解密）
    XorCipher(business_data, business_len);

    return strncmp(header->crc32, expected_crc, 8) == 0;
}

