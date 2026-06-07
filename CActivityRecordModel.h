#pragma once
#include<iostream>
#include<string>
#include"MysqlUtil.h"
#include "ActivityRecord.h"
#include"protecol.h"
#include<string.h>
#include <vector>
using namespace std;
class CActivityRecordModel
{
public:
	CActivityRecordModel();
	~CActivityRecordModel();
	bool insertActivityRecord(ActivityRecord activityRecord ,string phone);
	vector<ActivityRecord1> selectByPhone(string phone);
};

