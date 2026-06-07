#include "CSendVideoTask.h"

CSendVideoTask::CSendVideoTask(char* data, shmWrite* p) :CBaseTask(data)
{
	this->p = p;
}

CSendVideoTask::~CSendVideoTask()
{
}

void CSendVideoTask::working()
{
	//准备数据
	CPictrue picture;
	bool res = false;
	char sendBuf[8192] = { 0 };
	bzero(sendBuf, sizeof(HEAD) + sizeof(VIDEO_RESP));
	VIDEO_REQ video_req = { 0 };
	VIDEO_RESP video_resp = { 0 };
	HEAD head = {};
	Video video;
	cout << "23" << endl;
	//拷贝数据
	memcpy(&head, data, sizeof(HEAD));
	memcpy(&video_req, data + sizeof(HEAD), sizeof(VIDEO_REQ));
	//更改头中的信息
	head.data_len = sizeof(VIDEO_RESP);
	video = video_req.video;
	//判断业务类型
	if (video_req.type == 0)//插入数据
	{
		cout << "33" << endl;
		CVideoModel* videomodel = (CVideoModel*)ModelFactory::getInstance()->getModel(T_VIDEO);
		CPictureModel* picturemodel = (CPictureModel*)ModelFactory::getInstance()->getModel(T_PICTURE);
		//执行插入视频数据
		res = videomodel->insertNewVideo(video, video_req.phone);
		//赋值给CPictrue
		picture.setPicturename(video.cover_path);
		picture.setPicturetime(video.video_time);
		picture.setPicturetype(4);//封面
		if (res == true)//插入成功
		{
			cout << "44" << endl;
			cout << "视频插入成功44" << endl;

			res = picturemodel->insertPicture(picture, video_req.phone);
			if (res == true)
			{
				video_resp.status_code = 0;
				strcpy(video_resp.document_name, video_req.video.video_name);
				cout << "封面插入成功" << endl;
			}
			else
			{
				video_resp.status_code = 1;
				strcpy(video_resp.document_name, video_req.video.video_name);
				strcpy(video_resp.error_message, "封面图片插入失败");
				cout << "封面插入失败" << endl;
			}
		}
		else
		{
			video_resp.status_code = 1;
			strcpy(video_resp.document_name, video_req.video.video_name);
			strcpy(video_resp.error_message, "视频插入失败");
			cout << "视频插入失败" << endl;

		}
		//delete videomodel;
	}
	else if (video_req.type == 1)//更新数据
	{
		CVideoModel* videomodel = (CVideoModel*)ModelFactory::getInstance()->getModel(T_VIDEO);
		//执行插入视频数据
		res = videomodel->updateVideo(video, video_req.phone);
		if (res == true)//插入成功
		{
			video_resp.status_code = 0;
			strcpy(video_resp.document_name, video_req.video.video_name);
			cout << "视频信息更新成功" << endl;
		}
		else
		{
			video_resp.status_code = 1;
			strcpy(video_resp.document_name, video_req.video.video_name);
			strcpy(video_resp.error_message, "视频信息更新失败");
			cout << "视频信息更新失败" << endl;

		}
		//delete videomodel;
	}
	memcpy(sendBuf, &head, sizeof(HEAD));
	memcpy(sendBuf + sizeof(HEAD), &video_resp, sizeof(VIDEO_RESP));
	p->write_shm(sendBuf);
	bzero(sendBuf, sizeof(HEAD) + sizeof(VIDEO_RESP));
}
