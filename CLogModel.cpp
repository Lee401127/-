#include "CLogModel.h"
#include <ctime>

static string logNowString()
{
	char tbuf[32] = { 0 };
	time_t now = time(nullptr);
	struct tm tm_buf;
	localtime_r(&now, &tm_buf);
	strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S", &tm_buf);
	return string(tbuf);
}

bool CLogModel::quickLogByPhone(const string& phone, const string& function, const string& type, const string& info)
{
	if (phone.empty())
		return false;
	CLog l;
	l.setLogfunction(function);
	l.setLogtype(type);
	l.setDatetime(logNowString());
	l.setLoginfo(info);
	return insertlog(l, phone);
}

CLogModel::CLogModel()
{
}

CLogModel::~CLogModel()
{
}

bool CLogModel::insertlog(CLog log, string phone)
{
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "insert into log (user_id,log_function,log_type,log_time,log_info) values((select user_id from user where user_phone=?),?,?,?,?)";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setString(1, phone);
        pstmt->setString(2, log.getLogfunction());
        pstmt->setString(3, log.getLogtype());
        pstmt->setString(4, log.getDatetime());
        pstmt->setString(5, log.getLoginfo());


        int res = pstmt->executeUpdate();
        MysqlUtil::getInstance()->relesseDb(pstmt, NULL, conn);
        return true;

    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL sr=tatus:" << e.getSQLState() << endl;

    }
    return false;
}

list<CLog*> CLogModel::selectLogByUserID(int user_id)
{
    try
    {


        list<CLog*> loglist;    //����������ȡ��ѯ�û�
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "select * from log where user_id= ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setInt(1, user_id);
        ResultSet* rs = pstmt->executeQuery();
        //���������?
        while (rs->next())
        {

            CLog* log = new CLog();
            //set����
            log->setLogid(rs->getInt("log_id"));
            log->setUserid(rs->getInt("user_id"));
            log->setLogfunction(rs->getString("log_function"));  //����
            log->setLogtype(rs->getString("log_type"));
            log->setDatetime(rs->getString("log_time"));
            log->setLoginfo(rs->getString("log_info"));



            loglist.push_back(log);

        }
        //�ͷ���Դ
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);

        return loglist;
    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL sr=tatus:" << e.getSQLState() << endl;
        return list<CLog*>();
    }

}
