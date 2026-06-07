#include "CCaptureTask.h"

CCaptureTask::CCaptureTask(char* data, shmWrite* p) :CBaseTask(data)
{
	this->p = p;
}

CCaptureTask::~CCaptureTask()
{
}

void CCaptureTask::working()
{
	CPictrue picture;
	//准备数据
	char sendBuf[8192] = { 0 };
	bzero(sendBuf, sizeof(HEAD) + sizeof(PICTURE_RESP));
	HEAD head = {};
	PICTURE_REQ picture_req;
	PICTURE_RESP picture_resp = { 0 };
	bool res;
	//拷贝数据
	memcpy(&head, data, sizeof(HEAD));
	memcpy(&picture_req, data + sizeof(HEAD), sizeof(PICTURE_REQ));
	//更改头中信息
	head.data_len = sizeof(PICTURE_RESP);
	//拷贝传输的数据到 picture
	picture.setPicturename(picture_req.picture.picture_name);
	picture.setPicturetime(picture_req.picture.picture_time);
	picture.setPicturetype(picture_req.picture.picture_type);
	//插入图片
	CPictureModel* carmodel = (CPictureModel*)ModelFactory::getInstance()->getModel(T_PICTURE);
	res = carmodel->insertPicture(picture, picture_req.phone);
	if (res == true)
	{
		cout << "抓拍成功" << endl;
		picture_resp.status_code = 0;
		strcpy(picture_resp.document_name, picture_req.picture.picture_name);
	}
	else
	{
		cout << "抓拍失败" << endl;
		picture_resp.status_code = 1;
		strcpy(picture_resp.document_name, picture_req.picture.picture_name);
		strcpy(picture_resp.error_message, "插入数据库失败");
	}
	// carmodel 来自 ModelFactory 单例缓存，不能在任务里 delete
	//拷贝信息
	memcpy(sendBuf, &head, sizeof(HEAD));
	memcpy(sendBuf + sizeof(HEAD), &picture_resp, sizeof(PICTURE_RESP));
	p->write_shm(sendBuf);
	bzero(sendBuf, sizeof(HEAD) + sizeof(PICTURE_RESP));
}
