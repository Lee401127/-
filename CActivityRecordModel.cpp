#include "CActivityRecordModel.h"

CActivityRecordModel::CActivityRecordModel()
{
}

CActivityRecordModel::~CActivityRecordModel()
{
}

bool CActivityRecordModel::insertActivityRecord(ActivityRecord activityRecord, string phone)
{
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();

        // 将字符串活动类型转换为数据库的 tinyint 代码
        int activityTypeCode = 0;
        string typeStr = activityRecord.getActivityType();
        if (typeStr == "1" || typeStr == "起床") {
            activityTypeCode = 1;
        }
        else if (typeStr == "2" || typeStr == "用餐") {
            activityTypeCode = 2;
        }
        else if (typeStr == "3" || typeStr == "散步") {
            activityTypeCode = 3;
        }
        else if (typeStr == "4" || typeStr == "服药") {
            activityTypeCode = 4;
        }
        else if (typeStr == "其他") {
            activityTypeCode = 5;
        }
        else {
            // 如果传入未知类型，可根据需要处理，这里默认设为5（其他）
            activityTypeCode = 5;
        }

        string sql = "insert into activity_record(elder_id, activity_type, start_time, end_time, remark) "
            "values(?, ?, ?, ?, ?)";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setString(1, phone);
        pstmt->setInt(2, activityTypeCode);
        pstmt->setString(3, activityRecord.getStartTime());
        pstmt->setString(4, activityRecord.getEndTime());
        pstmt->setString(5, activityRecord.getRemark());

        pstmt->executeUpdate();

        MysqlUtil::getInstance()->relesseDb(pstmt, NULL, conn);

        cout << "活动记录插入成功" << endl;
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

vector<ActivityRecord1> CActivityRecordModel::selectByPhone(string phone)
{
    vector<ActivityRecord1> list;
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "select activity_type, start_time, end_time "
            "from activity_record where elder_id = ? order by start_time desc limit ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setString(1, phone);
        pstmt->setInt(2, MAX_OLD);
        ResultSet* rs = pstmt->executeQuery();
        while (rs->next())
        {
            ActivityRecord1 rec = {};
            int typeCode = rs->getInt("activity_type");
            // 统一回传数字码，客户端再映射中文，避免跨端编码乱码
            snprintf(rec.activityType, sizeof(rec.activityType), "%d", typeCode);
            string start = rs->getString("start_time");
            string end = rs->getString("end_time");
            strncpy(rec.startTime, start.c_str(), sizeof(rec.startTime) - 1);
            strncpy(rec.nendTime, end.c_str(), sizeof(rec.nendTime) - 1);
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
