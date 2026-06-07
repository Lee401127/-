#pragma once
#include<string>
#include<iostream>
using namespace std;
class CLog
{


private:
    int log_id;	//日志id
    int user_id;	//用户id
    string log_function;//功能
    string log_type;	//操作类型(发送接收)
    string datetime;	//操作时间
    string log_info;	//操作描述



public:
    int getLogid() const;
    void setLogid(int logid);           

    int getUserid() const;
    void setUserid(int userid);

    string getLogfunction() const;
    void setLogfunction(string logfunction);

    string getLogtype() const;
    void setLogtype(string logtype);

    string getDatetime() const;
    void setDatetime(string datetime);

    string getLoginfo() const;
    void setLoginfo(string loginfo);

};
