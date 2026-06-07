#include "CMedicineRecordModel.h"

CMedicineRecordModel::CMedicineRecordModel()
{
}

CMedicineRecordModel::~CMedicineRecordModel()
{
}

bool CMedicineRecordModel::insertMedicineRecord(MedicineRecord medicineRecord, string phone)
{
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();

        // 注意：数据库表中字段名为 frequency，对应 MedicineRecord 中的 usage
        string sql = "insert into medication_record(elder_id, medicine_name, dosage, frequency, record_time, remark) "
            "values(?, ?, ?, ?, ?, ?)";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setString(1, phone);
        pstmt->setString(2, medicineRecord.getMedicineName());
        pstmt->setString(3, medicineRecord.getDosage());
        pstmt->setString(4, medicineRecord.getUsage());   // usage -> frequency
        pstmt->setString(5, medicineRecord.getRecordTime());
        pstmt->setString(6, medicineRecord.getRemark());

        int res = pstmt->executeUpdate();

        MysqlUtil::getInstance()->relesseDb(pstmt, NULL, conn);

        cout << "用药记录插入成功" << endl;
        return true;
    }
    catch (sql::SQLException& e)
    {
        cout << "Error: " << e.what() << endl;
        cout << "Mysql error code: " << e.getErrorCode() << endl;
        cout << "SQL status: " << e.getSQLState() << endl;
        return false;
    }
}

std::vector<MedicineRecord1> CMedicineRecordModel::selectByPhone(std::string phone)
{
    std::vector<MedicineRecord1> list;
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "select medicine_name, dosage, record_time, frequency, remark "
            "from medication_record where elder_id = ? order by record_time desc limit ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setString(1, phone);
        pstmt->setInt(2, MAX_OLD);
        ResultSet* rs = pstmt->executeQuery();
        while (rs->next())
        {
            MedicineRecord1 rec = {};
            string name = rs->getString("medicine_name");
            string dosage = rs->getString("dosage");
            string time = rs->getString("record_time");
            string usage = rs->getString("frequency");
            string remark = rs->getString("remark");
            strncpy(rec.medicineName, name.c_str(), sizeof(rec.medicineName) - 1);
            strncpy(rec.dosage, dosage.c_str(), sizeof(rec.dosage) - 1);
            strncpy(rec.recordTime, time.c_str(), sizeof(rec.recordTime) - 1);
            strncpy(rec.usage, usage.c_str(), sizeof(rec.usage) - 1);
            strncpy(rec.remark, remark.c_str(), sizeof(rec.remark) - 1);
            list.push_back(rec);
        }
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
    }
    catch (sql::SQLException& e)
    {
        cout << "Error: " << e.what() << endl;
        cout << "Mysql error code: " << e.getErrorCode() << endl;
        cout << "SQL status: " << e.getSQLState() << endl;
    }
    return list;
}
