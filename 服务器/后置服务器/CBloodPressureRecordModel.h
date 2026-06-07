#pragma once
#include<iostream>
#include<string>
#include"MysqlUtil.h"
#include "BloodPressureRecord.h"
#include"protecol.h"
#include<string.h>
#include <vector>
using namespace std;
class CBloodPressureRecordModel
{
public:
	CBloodPressureRecordModel();
	~CBloodPressureRecordModel();
	bool insertBloodPressureRecord(BloodPressureRecord bloodPressureRecord, string phone);
	vector<BloodPressureRecord1> selectByPhone(string phone);
};

