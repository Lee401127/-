#include "CBloodPressureRecordModel.h"

CBloodPressureRecordModel::CBloodPressureRecordModel()
{
}

CBloodPressureRecordModel::~CBloodPressureRecordModel()
{
}

bool CBloodPressureRecordModel::insertBloodPressureRecord(BloodPressureRecord bloodPressureRecord, string phone)
{
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();

        // elder_id 已改为手机号主键，直接使用请求中的 phone
        string sql = "insert into blood_pressure_record(elder_id, systolic, diastolic, record_time, remark) "
            "values(?, ?, ?, ?, ?)";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setString(1, phone);
        pstmt->setInt(2, bloodPressureRecord.getSystolic());
        pstmt->setInt(3, bloodPressureRecord.getDiastolic());
        pstmt->setString(4, bloodPressureRecord.getMeasureTime());
        pstmt->setString(5, bloodPressureRecord.getRemark());

        pstmt->executeUpdate();

        MysqlUtil::getInstance()->relesseDb(pstmt, NULL, conn);

        cout << "血压记录插入成功" << endl;
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

vector<BloodPressureRecord1> CBloodPressureRecordModel::selectByPhone(string phone)
{
    vector<BloodPressureRecord1> list;
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "select systolic, diastolic, record_time, remark "
            "from blood_pressure_record where elder_id = ? order by record_time desc limit ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setString(1, phone);
        pstmt->setInt(2, MAX_OLD);
        ResultSet* rs = pstmt->executeQuery();
        while (rs->next())
        {
            BloodPressureRecord1 rec = {};
            rec.systolic = rs->getInt("systolic");
            rec.diastolic = rs->getInt("diastolic");
            string tm = rs->getString("record_time");
            string remark = rs->getString("remark");
            strncpy(rec.measureTime, tm.c_str(), sizeof(rec.measureTime) - 1);
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
