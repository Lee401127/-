#include "CLog.h"

int CLog::getLogid() const
{
    return log_id;
}

void CLog::setLogid(int logid)
{
    log_id = logid;
}

int CLog::getUserid() const
{
    return user_id;
}

void CLog::setUserid(int userid)
{
    user_id = userid;
}

string CLog::getLogfunction() const
{
    return log_function;
}

void CLog::setLogfunction(string logfunction)
{
    log_function = logfunction;
}

string CLog::getLogtype() const
{
    return log_type;
}

void CLog::setLogtype(string logtype)
{
    log_type = logtype;
}

string CLog::getDatetime() const
{
    return datetime;
}

void CLog::setDatetime(string datetime)
{
    this->datetime = datetime;
}

string CLog::getLoginfo() const
{
    return log_info;
}

void CLog::setLoginfo(string loginfo)
{
    log_info = loginfo;
}

