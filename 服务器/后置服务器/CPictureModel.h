#pragma once
#include<iostream>
#include<string>
#include"MysqlUtil.h"
#include "CPictrue.h"
#include"protecol.h"
#include<string.h>
using namespace std;
class CPictureModel
{
public:
	CPictureModel();
	~CPictureModel();
	//插入一条图片信息
	bool insertPicture(CPictrue picture, string phone);

	//查询当天视频(使用Video数组保留)
	Picture* SelectDayPictureByPhone(int start, int end, string datatime);
	//查询一个月视频(使用Video数组保留)
	Picture* SelectMonthPictureByPhone(int start, int end, string datatime);
	//查询按天的时间列表
	vector<string> SelectDataList(int from, int end);
	//查询按月的时间列表
	vector<string> SelectMonthList(int from, int end);
};

