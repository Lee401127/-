#pragma once

#include <iostream>
#include <cstring>
#include <cstdint>
#include <vector>
#include "protecol.h"
using namespace std;





class CRCUtil
{
public:
	explicit CRCUtil(char encryptionKey = 0x55);

	// 核心校验接口
	void GenerateChecksum(char* data, size_t len);
	bool ValidateData(const char* data, size_t len);

private:
	std::vector<uint32_t> crc_table_;
	bool table_generated_;
	char encryption_key_;

	void GenerateCrcTable();
	uint32_t CalculateCrc32(const void* data, size_t length) const;
	void XorCipher(char* data, size_t length) const;





};

