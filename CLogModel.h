#pragma once
#include "MysqlUtil.h"
#include<list>
#include "CLog.h"

class CLogModel
{
public:
	CLogModel();
	~CLogModel();
	//增加一条日志信息
	bool insertlog(CLog log, string phone);
	/** 按手机号解析 user_id 写日志（无用户则 insert 可能失败，忽略返回值即可） */
	bool quickLogByPhone(const string& phone, const string& function, const string& type, const string& info);
	//根据用户id查询日志信息
	list<CLog*> selectLogByUserID(int user_id);




};

