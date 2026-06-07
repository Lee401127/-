#pragma once
#include "CUserModel.h"
#include "CLogModel.h"
#include<map>
#include"COldModel.h"
#include "CPictureModel.h"
#include "CVideoModel.h"
#include"CActivityRecordModel.h"
#include"CBloodPressureRecordModel.h"
#include"CElderInfoModel.h"
#include"CMedicineRecordModel.h"
//工厂模式(分层解耦)
enum MODEL_NAME
{
	T_USER,	//用户
	T_LOG,	//日志

	T_PICTURE,	//图片
	T_VIDEO,		//视频
	T_OLD,	//老人
	T_ACTIVITY,//
	T_BLOOD,//
	T_ELDER,
	T_MEDICINE
};

class ModelFactory
{
public:
	void* getModel(enum MODEL_NAME model_name);
	static ModelFactory* getInstance();
private:
	ModelFactory();
	static ModelFactory* factory;
	map<enum MODEL_NAME, void*> modelMap;
};

