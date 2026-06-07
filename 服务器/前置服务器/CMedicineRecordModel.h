#pragma once
#include<iostream>
#include<string>
#include"MysqlUtil.h"
#include "MedicineRecord.h"
#include"protecol.h"
#include<string.h>
#include <vector>
class CMedicineRecordModel
{
public:
	CMedicineRecordModel();
	~CMedicineRecordModel();
	bool insertMedicineRecord(MedicineRecord medicineRecord, string phone);
	std::vector<MedicineRecord1> selectByPhone(std::string phone);
};

