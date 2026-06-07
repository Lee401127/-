#pragma once
#include"CVideo.h"
#include "MysqlUtil.h"
#include"protecol.h"
#include<string>
#include<vector>
class CVideoModel
{
public:
	CVideoModel();
	~CVideoModel();
	//更新视频信息(图片名称是唯一的)
	bool updateVideo(Video video, string phone);
	//插入新的视频信息
	bool insertNewVideo(Video video, string phone);

	//查询当天视频(使用Video数组保留)
	Video* SelectDayVideoByPhone(int start, int end, string datatime);
	//查询一个月视频(使用Video数组保留)
	Video* SelectMonthVideoByPhone(int start, int end, string datatime);
	//查询按天的时间列表
	vector<string> SelectDataList(int from, int end);
	//查询按月的时间列表
	vector<string> SelectMonthList(int from, int end);
};

