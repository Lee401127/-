#pragma once
/*
    Mysql数据库工具类
    连接数据库
    释放资源
*/

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <mysql.h>
#include <string>

using namespace std;
using namespace sql::mysql;
using namespace sql;
/*
    单例步骤
    1.私有化构造
    2.定义静态的的本类对象指针,用于保存当前对象
    3.提供一个公有的静态的获取当前对象的方法
*/
class MysqlUtil
{
public:
    //获取连接
    Connection* getConnection();
    //释放资源
    void relesseDb(PreparedStatement* pstmt, ResultSet* rs, Connection* conn);
    //获取实例
    static MysqlUtil* getInstance();
private:
    MysqlUtil();
    static MysqlUtil* mysqlUtil;
    string url;
    string username;
    string password;
    string dbname;
    MySQL_Driver* driver;

};