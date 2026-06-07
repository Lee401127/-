#include "CGetVideoListTask.h"

CGetVideoListTask::CGetVideoListTask(char* data, shmWrite* p) :CBaseTask(data)
{
	this->p = p;
}

CGetVideoListTask::~CGetVideoListTask()
{
}

void CGetVideoListTask::working()
{
	//准备数据
	bool res = false;
	char sendBuf[8192] = { 0 };
	bzero(sendBuf, sizeof(HEAD) + sizeof(GET_VIDEO_REQ));
	GET_VIDEO_REQ getvideo_req = { 0 };
	GET_VIDEO_RESP getvideo_resp = { 0 };
	HEAD head = {};
	Video* video = new Video[MAX_VIDEO];
	vector<string> videodatelist;
	char datetime[MAX_DATE][20];// 左侧日期列表
	//拷贝数据
	memcpy(&head, data, sizeof(HEAD));
	memcpy(&getvideo_req, data + sizeof(HEAD), sizeof(GET_VIDEO_REQ));
	//更改头中的信息
	head.data_len = sizeof(GET_VIDEO_RESP);
	//先去判断to-from的值
	if (getvideo_req.to - getvideo_req.from > 0 && getvideo_req.to - getvideo_req.from <= 20)
	{
		//去判断是哪个业务(0 按月查询  1 按日查询  -1视频列表查询)
		if (getvideo_req.type >= 0)
		{
			cout << "35" << getvideo_req.type << endl;
			if (getvideo_req.type == 0)
			{
				cout << "执行了左侧时间的按月查询" << endl;
				CVideoModel* videomodel = (CVideoModel*)ModelFactory::getInstance()->getModel(T_VIDEO);
				videodatelist = videomodel->SelectMonthList(getvideo_req.from, getvideo_req.to);

			}
			else if (getvideo_req.type == 1)
			{
				cout << "执行了左侧时间的按日查询" << endl;
				CVideoModel* videomodel = (CVideoModel*)ModelFactory::getInstance()->getModel(T_VIDEO);
				videodatelist = videomodel->SelectDataList(getvideo_req.from, getvideo_req.to);

			}
			else if (getvideo_req.type == 2)
			{
				cout << "执行了查询视频信息" << endl;

				CVideoModel* videomodel = (CVideoModel*)ModelFactory::getInstance()->getModel(T_VIDEO);
				if (strlen(getvideo_req.time) == 10)//按天查询
				{
					video = videomodel->SelectDayVideoByPhone(getvideo_req.from, getvideo_req.to, getvideo_req.time);
				}
				else if (strlen(getvideo_req.time) == 7)//按月查询
				{
					video = videomodel->SelectMonthVideoByPhone(getvideo_req.from, getvideo_req.to, getvideo_req.time);
				}

				cout << "getvideo_req.to - getvideo_req.from:" << getvideo_req.to - getvideo_req.from << endl;
				for (int i = 0; i < (getvideo_req.to - getvideo_req.from); i++)
				{

					getvideo_resp.video_arr[i] = video[i];
					cout << "69" << getvideo_resp.video_arr[i].cover_path << endl;
				}
				cout << "71" << getvideo_resp.video_arr[0].cover_path << endl;
				getvideo_resp.status_code = 0;

			}

			if (videodatelist.size() > 0 && getvideo_req.type == 0 || getvideo_req.type == 1)
			{
				//赋值给二维数组
				for (int i = 0; i < videodatelist.size(); i++)
				{
					for (int j = 0; j < videodatelist[i].size(); j++)
					{
						datetime[i][j] = videodatelist[i].c_str()[j];
					}
					datetime[i][videodatelist[i].size()] = '\0';
				}
				for (int i = 0; i < videodatelist.size(); i++)
				{
					//cout << "查询到的左侧日期数据是:" << datetime[i] << endl;
					strcpy(getvideo_resp.datetime[i], datetime[i]);
					cout << "getvideo_resp.datetime[i]:" << getvideo_resp.datetime[i] << endl;
				}
				getvideo_resp.status_code = 0;
			}


		}
	}
	else
	{
		strcpy(getvideo_resp.error_message, "104传入的from和to不符合要求");
		getvideo_resp.status_code = 1;
	}
	memcpy(sendBuf, &head, sizeof(HEAD));
	memcpy(sendBuf + sizeof(HEAD), &getvideo_resp, sizeof(GET_VIDEO_RESP));
	p->write_shm(sendBuf);
	bzero(sendBuf, sizeof(HEAD) + sizeof(GET_VIDEO_RESP));



}
