#pragma once
#include<iostream>
#include<string>
#include"MysqlUtil.h"
#include "ElderInfo.h"
#include"protecol.h"
#include<string.h>

using namespace std;
class CElderInfoModel
{
public:
	CElderInfoModel();
	~CElderInfoModel();
	bool insertCElderInfo(ElderInfo elderinfo, string phone);
	bool selectCElderInfoByPhone(const string& phone, ElderInfo& elderinfo);
	/** Contact field = family login phone and user.identity_id=0 -> insert family_elder; else skip */
	bool syncFamilyElderBinding(const string& elderPhone, const string& contactPhone);

};
