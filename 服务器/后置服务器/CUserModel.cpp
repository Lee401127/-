#include "CUserModel.h"
#include <string.h>

CUserModel::CUserModel()
{
}

CUserModel::~CUserModel()
{
}

//??????????(???)?????????
//1.???????list<CUser*>??????????????????????,
//2.???????????????????
list<CUser*> CUserModel::selectByPhone(char phone[12])
{

    try
    {


        list<CUser*> userlist;    //?????????????????
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "select * from user where user_phone= ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setString(1, phone);
        ResultSet* rs = pstmt->executeQuery();
        //?????????
        while (rs->next())
        {
            cout << "?????select31" << endl;
            CUser* u = new CUser();
            //set????
            u->setUserid(rs->getInt("user_id"));
            u->setUserphone(rs->getString("user_phone"));
            u->setUsernike(rs->getString("user_nike"));
            u->setUserpassword(rs->getString("user_password"));
            u->setKind(rs->getInt("identity_id"));
            //u->setStatus(rs->getInt("user_status"));
            userlist.push_back(u);
            delete u;
        }
        //??????
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);

        return userlist;
    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL sr=tatus:" << e.getSQLState() << endl;

    }

}


bool CUserModel::insertUser(CUser u)
{

    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "insert into user (user_phone,user_nike,user_password,identity_id) values(?,?,?,?)";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setString(1, u.getUserphone());
        pstmt->setString(2, u.getUsernike());
        pstmt->setString(3, u.getUserpassword());
        pstmt->setInt(4, u.getKind());


        int res = pstmt->executeUpdate();
        MysqlUtil::getInstance()->relesseDb(pstmt, NULL, conn);
        return true;

    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL sr=tatus:" << e.getSQLState() << endl;
        return false;

    }


 

}
//??????????????0,????????????1
bool CUserModel::updateStatusByPhone(char phone[12], int status)
{
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "update user set user_status= ? where user_phone= ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setInt(1, status);
        pstmt->setString(2, phone);
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

list<CUser*> CUserModel::selectByphoneAndPwd(string phone, string password)
{
    list<CUser*> userlists;
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "select * from user where user_phone= ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setString(1, phone);

        ResultSet* rs = pstmt->executeQuery();
        //?????????
        while (rs->next())
        {
            if (password == rs->getString("user_password"))
            {
                CUser* us = new CUser();
                us->setUserid(rs->getInt("user_id"));
                us->setUserphone(rs->getString("user_phone"));
                us->setUsernike(rs->getString("user_nike"));
                us->setUserpassword(rs->getString("user_password"));
                us->setKind(rs->getInt("identity_id"));
                userlists.push_back(us);
            }
        }
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
        return userlists;
    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        return userlists;
    }
}

int CUserModel::getIdentityIfPasswordOk(const string& phone, const string& password)
{
    try {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "select identity_id from user where user_phone = ? and user_password = ? limit 1";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setString(1, phone);
        pstmt->setString(2, password);
        ResultSet* rs = pstmt->executeQuery();
        int k = -1;
        if (rs->next())
            k = rs->getInt("identity_id");
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
        return k;
    }
    catch (sql::SQLException& e)
    {
        cout << "getIdentityIfPasswordOk: " << e.what() << endl;
        return -1;
    }
}
