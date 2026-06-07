#include "CVideoModel.h"
#include<string.h>
CVideoModel::CVideoModel()
{
}

CVideoModel::~CVideoModel()
{
}

bool CVideoModel::updateVideo(Video video, string phone)
{
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "update video set video_current= ? ,last_play_time= ? where user_id= (select user_id from user where user_phone= ? ) and video_name= ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setInt(1, video.video_current);
        pstmt->setString(2, video.video_starttime);
        pstmt->setString(3, phone);
        pstmt->setString(4, video.video_name);
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

bool CVideoModel::insertNewVideo(Video video, string phone)
{
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "insert into video (user_id,video_name,cover_path,video_time,video_current,video_alltime,last_play_time) values((select user_id from user where user_phone= ? ),?,?,?,?,?,?)";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setString(1, phone);
        pstmt->setString(2, video.video_name);
        pstmt->setString(3, video.cover_path);
        pstmt->setString(4, video.video_time);
        pstmt->setInt(5, video.video_current);
        pstmt->setInt(6, video.video_alltime);
        pstmt->setString(7, video.video_starttime);
        int res = pstmt->executeUpdate();
        MysqlUtil::getInstance()->relesseDb(pstmt, NULL, conn);
        cout << "视频表插入成功" << endl;
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
Video* CVideoModel::SelectMonthVideoByPhone(int start, int end, string datatime)
{

    Video* video = new Video[MAX_VIDEO];
    int i = 0;
    try
    {

        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "select * from video where date_format(video_time,'%Y-%m')= ? limit ? offset ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setString(1, datatime);
        pstmt->setInt(2, end - start);
        pstmt->setInt(3, start);


        ResultSet* rs = pstmt->executeQuery();
        //遍历结果集
        while (rs->next())
        {
            cout << "执行了月份select" << endl;
            strcpy(video[i].cover_path, rs->getString("cover_path").c_str());
            strcpy(video[i].video_name, rs->getString("video_name").c_str());
            strcpy(video[i].video_time, rs->getString("video_time").c_str());
            video[i].video_current = rs->getInt("video_current");
            video[i].video_alltime = rs->getInt("video_alltime");
            strcpy(video[i].video_starttime, rs->getString("last_play_time").c_str());
            i++;

        }
        return video;
        //释放资源
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL sr=tatus:" << e.getSQLState() << endl;

    }











}
vector<string> CVideoModel::SelectDataList(int from, int end)
{
    vector<string> vectorDate;
    int res = end - from;
    try
    {

        Connection* conn = MysqlUtil::getInstance()->getConnection();
        cout << "111" << endl;
        string sql = "select distinct date_format(video_time,'%Y-%m-%d') from  video order by date_format(video_time,'%Y-%m-%d') asc limit ? offset ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        cout << "222" << endl;
        pstmt->setInt(1, res);
        pstmt->setInt(2, from);

        ResultSet* rs = pstmt->executeQuery();
        //遍历结果集
        while (rs->next())
        {
            cout << "执行了日期列表select查询" << endl;
            vectorDate.push_back(rs->getString("date_format(video_time,'%Y-%m-%d')").substr(0, 10));
        }
        return vectorDate;
        //释放资源
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL sr=tatus:" << e.getSQLState() << endl;

    }



}
vector<string> CVideoModel::SelectMonthList(int from, int end)
{
    vector<string> vectorDate;
    try
    {

        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "select distinct date_format(video_time,'%Y-%m') from  video order by date_format(video_time,'%Y-%m') asc limit ? offset ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setInt(1, end - from);
        pstmt->setInt(2, from);

        ResultSet* rs = pstmt->executeQuery();
        //遍历结果集
        while (rs->next())
        {
            cout << "执行了月份列表select查询" << endl;
            vectorDate.push_back(rs->getString("date_format(video_time,'%Y-%m')").substr(0, 7));

        }
        return vectorDate;
        //释放资源
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL sr=tatus:" << e.getSQLState() << endl;

    }
}
//查询当天视频列表
Video* CVideoModel::SelectDayVideoByPhone(int start, int end, string datatime)
{
    Video* video = new Video[MAX_VIDEO];
    int i = 0;
    try
    {

        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql = "select * from video where date_format(video_time,'%Y-%m-%d')= ? limit ? offset ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setString(1, datatime);
        pstmt->setInt(2, end - start);
        pstmt->setInt(3, start);


        ResultSet* rs = pstmt->executeQuery();
        //遍历结果集
        while (rs->next())
        {
            cout << "执行了日期select查询" << endl;
            strcpy(video[i].cover_path, rs->getString("cover_path").c_str());
            strcpy(video[i].video_name, rs->getString("video_name").c_str());
            strcpy(video[i].video_time, rs->getString("video_time").c_str());
            video[i].video_current = rs->getInt("video_current");
            video[i].video_alltime = rs->getInt("video_alltime");
            strcpy(video[i].video_starttime, rs->getString("last_play_time").c_str());
            i++;
        }
        return video;
        //释放资源
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL sr=tatus:" << e.getSQLState() << endl;

    }






}




