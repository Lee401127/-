#include "CGetPictureListTask.h"

CGetPictureListTask::CGetPictureListTask(char* data, shmWrite* p) :CBaseTask(data)
{
	this->p = p;
}

CGetPictureListTask::~CGetPictureListTask()
{
}

void CGetPictureListTask::working()
{
	//准备数据
	bool res = false;
	char sendBuf[8192] = { 0 };
	bzero(sendBuf, sizeof(HEAD) + sizeof(GET_PICTURE_REQ));
	GET_PICTURE_REQ getpicture_req = { 0 };
	GET_PICTURE_RESP getpicture_resp = { 0 };
	HEAD head = {};
	Picture* picture = nullptr;
	vector<string> picturedatelist;
	char datetime[MAX_DATE][20];// 左侧日期列表
	//拷贝数据
	memcpy(&head, data, sizeof(HEAD));
	memcpy(&getpicture_req, data + sizeof(HEAD), sizeof(GET_PICTURE_REQ));
	//更改头中的信息
	head.data_len = sizeof(GET_PICTURE_RESP);
	//先去判断to-from的值
	if (getpicture_req.to - getpicture_req.from > 0 && getpicture_req.to - getpicture_req.from <= 20)
	{
		//去判断是哪个业务(0 按月查询  1 按日查询  -1视频列表查询)
		if (getpicture_req.type >= 0)
		{
			cout << "35" << getpicture_req.type << endl;
			if (getpicture_req.type == 0)
			{
				cout << "执行了左侧时间的按月查询" << endl;
				CPictureModel* picturemodel = (CPictureModel*)ModelFactory::getInstance()->getModel(T_PICTURE);
				picturedatelist = picturemodel->SelectMonthList(getpicture_req.from, getpicture_req.to);

			}
			else if (getpicture_req.type == 1)
			{
				cout << "执行了左侧时间的按日查询" << endl;
				CPictureModel* picturemodel = (CPictureModel*)ModelFactory::getInstance()->getModel(T_PICTURE);
				picturedatelist = picturemodel->SelectDataList(getpicture_req.from, getpicture_req.to);

			}
			else if (getpicture_req.type == 2)
			{
				cout << "执行了查询图片信息" << endl;

				CPictureModel* picturemodel = (CPictureModel*)ModelFactory::getInstance()->getModel(T_PICTURE);
				if (strlen(getpicture_req.time) == 10)//按天查询
				{
					picture = picturemodel->SelectDayPictureByPhone(getpicture_req.from, getpicture_req.to, getpicture_req.time);
				}
				else if (strlen(getpicture_req.time) == 7)//按月查询
				{
					picture = picturemodel->SelectMonthPictureByPhone(getpicture_req.from, getpicture_req.to, getpicture_req.time);
				}

				if (picture != nullptr)
				{
					int cnt = getpicture_req.to - getpicture_req.from;
					if (cnt > MAX_PICTURE) cnt = MAX_PICTURE;
					if (cnt < 0) cnt = 0;

					for (int i = 0; i < cnt; i++)
					{
						getpicture_resp.picture_arr[i] = picture[i];
						// cout << "pic " << i << ":" << getpicture_resp.picture_arr[i].picture_name << endl;
					}

					getpicture_resp.status_code = 0;
					delete[] picture;
					picture = nullptr;
				}
				else
				{
					getpicture_resp.status_code = 1;
					strcpy(getpicture_resp.error_message, "图片查询失败：时间格式不合法或无返回数据");
				}

			}

			if (!picturedatelist.empty() && (getpicture_req.type == 0 || getpicture_req.type == 1))
			{
				//赋值给二维数组
				for (int i = 0; i < picturedatelist.size(); i++)
				{
					for (int j = 0; j < picturedatelist[i].size(); j++)
					{
						datetime[i][j] = picturedatelist[i].c_str()[j];
					}
					datetime[i][picturedatelist[i].size()] = '\0';
				}
				for (int i = 0; i < picturedatelist.size(); i++)
				{
					//cout << "查询到的左侧日期数据是:" << datetime[i] << endl;
					strcpy(getpicture_resp.datetime[i], datetime[i]);
					cout << "getpicture_resp.datetime[i]:" << getpicture_resp.datetime[i] << endl;
				}
				getpicture_resp.status_code = 0;
			}


		}
	}
	else
	{
		strcpy(getpicture_resp.error_message, "104传入的from和to不符合要求");
		getpicture_resp.status_code = 1;
	}
	memcpy(sendBuf, &head, sizeof(HEAD));
	memcpy(sendBuf + sizeof(HEAD), &getpicture_resp, sizeof(GET_PICTURE_RESP));
	p->write_shm(sendBuf);
	bzero(sendBuf, sizeof(HEAD) + sizeof(GET_PICTURE_RESP));


}
