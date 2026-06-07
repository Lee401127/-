#include"MysqlUtil.h"
MysqlUtil* MysqlUtil::mysqlUtil = nullptr;
Connection* MysqlUtil::getConnection()
{
    //2.连接mysql数据库
    Connection* conn = driver->connect(url, username, password);
    conn->setSchema(dbname);
    return conn;
}

void MysqlUtil::relesseDb(PreparedStatement* pstmt, ResultSet* rs, Connection* conn)
{
    if (rs != NULL)
        delete rs;
    if (pstmt != NULL)
        delete pstmt;
    if (conn != NULL)
    {
        conn->close();
        delete conn;
    }
}

MysqlUtil* MysqlUtil::getInstance()
{
    if (MysqlUtil::mysqlUtil == nullptr)
    {
        MysqlUtil::mysqlUtil = new MysqlUtil();
    }
    return MysqlUtil::mysqlUtil;
}
MysqlUtil::MysqlUtil()
{
    //从配置文件得到


    this->url = "tcp://127.0.0.1:3306";
    this->username = "root";
    this->password = "Abcd123!";
    this->dbname = "designdatabase";

    /*
    this->url = "tcp://139.198.30.172:3306";
    this->username = "root";
    this->password = "Cyzn_123";
    this->dbname = "ourdb";
     */


     //1.获取mysql数据库实例(数据库驱动)
    this->driver = sql::mysql::get_driver_instance();
}