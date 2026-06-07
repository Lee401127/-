#include "ModelFactory.h"
ModelFactory* ModelFactory::factory = NULL;
void* ModelFactory::getModel(MODEL_NAME model_name)
{
	return this->modelMap[model_name];
}
ModelFactory* ModelFactory::getInstance()
{
	if (ModelFactory::factory == NULL)
	{
		ModelFactory::factory = new ModelFactory();
	}
	return ModelFactory::factory;
}

ModelFactory::ModelFactory()
{
	this->modelMap[T_USER] = new CUserModel();
	this->modelMap[T_LOG] = new CLogModel();
	this->modelMap[T_PICTURE] = new CPictureModel();

	this->modelMap[T_VIDEO] = new CVideoModel();
	this->modelMap[T_OLD] = new COldModel();
	this->modelMap[T_ACTIVITY] = new CActivityRecordModel();
	this->modelMap[T_BLOOD] = new CBloodPressureRecordModel();

	this->modelMap[T_ELDER] = new CElderInfoModel();
	this->modelMap[T_MEDICINE] = new CMedicineRecordModel();
}
