#include "CPictureModel.h"

CPictureModel::CPictureModel()
{

}

CPictureModel::~CPictureModel()
{
}

bool CPictureModel::insertPicture(CPictrue picture, string phone)
{
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "insert into picture(user_id,picture_name,picture_time,picture_type) values((select user_id from user where user_phone= ? ),?,?,?)";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setString(1, phone);
        pstmt->setString(2, picture.getPicturename());
        pstmt->setString(3, picture.getPicturetime());
        pstmt->setInt(4, picture.getPicturetype());


        int res = pstmt->executeUpdate();
        MysqlUtil::getInstance()->relesseDb(pstmt, NULL, conn);
        cout << picture.getPicturename() << ":????????????" << endl;
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

Picture* CPictureModel::SelectDayPictureByPhone(int start, int end, string datatime)
{
    // Áã³õÊ¼»¯£º±ÜÃâÎ´±»Ìî³äµÄÔªËØÈÔº¬À¬»øÊý¾Ý£¬µ¼ÖÂ¿Í»§¶Ë strlen/picture_name ±ÀÀ£
    Picture* picture = new Picture[MAX_PICTURE]();
    int i = 0;
    try
    {

        Connection* conn = MysqlUtil::getInstance()->getConnection();
        // ?????????(3)????????????????/?????
        string sql = "select * from picture where date_format(picture_time,'%Y-%m-%d')= ? and picture_type=3 limit ? offset ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setString(1, datatime);
        pstmt->setInt(2, end - start);
        pstmt->setInt(3, start);


        ResultSet* rs = pstmt->executeQuery();
        //?????????
        while (rs->next())
        {
            if (i >= MAX_PICTURE) {
                // ??? SQL ??????? MAX_PICTURE ?????????????????
                break;
            }
            cout << "?????????select???" << endl;
            strcpy(picture[i].picture_name, rs->getString("picture_name").c_str());

            strcpy(picture[i].picture_time, rs->getString("picture_time").c_str());
            picture[i].picture_type = rs->getInt("picture_type");
            i++;
        }
        return picture;
        //??????
        return picture;

    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL sr=tatus:" << e.getSQLState() << endl;

    }

}

Picture* CPictureModel::SelectMonthPictureByPhone(int start, int end, string datatime)
{

    // Áã³õÊ¼»¯£º±ÜÃâÎ´±»Ìî³äµÄÔªËØÈÔº¬À¬»øÊý¾Ý£¬µ¼ÖÂ¿Í»§¶Ë strlen/picture_name ±ÀÀ£
    Picture* picture = new Picture[MAX_PICTURE]();
    int i = 0;
    try
    {

        Connection* conn = MysqlUtil::getInstance()->getConnection();
        // ?????????(3)????????????????/?????
        string sql = "select * from picture where date_format(picture_time,'%Y-%m')= ? and picture_type=3 limit ? offset ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setString(1, datatime);
        pstmt->setInt(2, end - start);
        pstmt->setInt(3, start);


        ResultSet* rs = pstmt->executeQuery();
        //?????????
        while (rs->next())
        {
            if (i >= MAX_PICTURE) {
                // ??? SQL ??????? MAX_PICTURE ?????????????????
                break;
            }
            cout << "??????¡¤?select" << endl;
            strcpy(picture[i].picture_name, rs->getString("picture_name").c_str());

            strcpy(picture[i].picture_time, rs->getString("picture_time").c_str());
            picture[i].picture_type = rs->getInt("picture_type");

            i++;

        }
        return picture;
        //??????
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL sr=tatus:" << e.getSQLState() << endl;

    }



}

vector<string> CPictureModel::SelectDataList(int from, int end)
{
    vector<string> vectorDate;
    int res = end - from;
    try
    {

        Connection* conn = MysqlUtil::getInstance()->getConnection();
        cout << "111" << endl;
        string sql = "select distinct date_format(picture_time,'%Y-%m-%d') from  picture order by date_format(picture_time,'%Y-%m-%d') asc limit ? offset ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        cout << "222" << endl;
        pstmt->setInt(1, res);
        pstmt->setInt(2, from);

        ResultSet* rs = pstmt->executeQuery();
        //?????????
        while (rs->next())
        {
            cout << "??????????§Ò?select???" << endl;
            vectorDate.push_back(rs->getString("date_format(picture_time,'%Y-%m-%d')").substr(0, 10));
        }
        return vectorDate;
        //??????
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL sr=tatus:" << e.getSQLState() << endl;

    }

}

vector<string> CPictureModel::SelectMonthList(int from, int end)
{
    vector<string> vectorDate;
    try
    {

        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "select distinct date_format(picture_time,'%Y-%m') from picture where picture_type=3 order by date_format(picture_time,'%Y-%m') asc limit ? offset ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setInt(1, end - from);
        pstmt->setInt(2, from);

        ResultSet* rs = pstmt->executeQuery();
        //?????????
        while (rs->next())
        {
            cout << "??????¡¤??§Ò?select???" << endl;
            vectorDate.push_back(rs->getString("date_format(picture_time,'%Y-%m')").substr(0, 7));

        }
        return vectorDate;
        //??????
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL sr=tatus:" << e.getSQLState() << endl;

    }
}
