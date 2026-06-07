#include<iostream>
#include "getCodeUtil.h"
#include "CUserModel.h"
#include "CLogModel.h"
#include "CLoginTask.h"
#include "CGetodeTask.h"
#include "CThreadPool.h"
#include "CRegisterTask.h"
#include "shmRead.h"
#include "CRCUtil.h"
#include "MD5.h"
#include "CDocumentTask.h"
#include "CPictureModel.h"

#include "CSendVideoTask.h"
#include "CCaptureTask.h"
#include "CVideoModel.h"
#include "CGetVideoListTask.h"
#include"CGetPictureListTask.h"
#include"CGetOldListTask.h"
#include "CinsertTask.h"
#include "CinsertTask2.h"
#include"CinsertTask3.h"
#include"CinsertTask4.h"
#include "CQueryElderInfoTask.h"
#include "CQueryBloodPressureTask.h"
#include "CQueryMedicineTask.h"
#include "CQueryActivityTask.h"
#include "CCallRecordReportTask.h"
#include "CCallRecordQueryTask.h"
using namespace std;



//???????
void demo1()
{
	getCodeUtil* getcode = new getCodeUtil("19712600936");

	cout << "??????????:" << getcode->getCode() << endl;
}
//??????????
void demo2()
{
	CUser u;
	bool res;
	list<CUser*> userlist;
	list<CUser*>::iterator it;
	CUserModel* user = new CUserModel();
	/*
	userlist = user->selectByPhone("17884878791");
	for (it = userlist.begin(); it != userlist.end(); it++)
	{
		cout << "???????:" << (*it)->getUsernike()<<endl;
	}
	*/
	//??????
	/*
	res = user->updateStatusByPhone("17884878791",1);
	if (res)
	{
		cout << "??????" << endl;
	}
	*/

	/*
	//????????
	u.setUserid(1002);
	u.setUserphone("13783368554");
	u.setUserpassword("123456");
	u.setStatus(0);
	u.setUsernike("????");
	res = user->insertUser(u);
	if (res)
	{
		cout << "??????" << endl;
	}*/


	//???????????
	userlist = user->selectByphoneAndPwd("17884878791", "123456");
	cout << "????" << userlist.size() << endl;



}
//???????
void demo3()
{
	bool res;
	CLogModel* log = new CLogModel();
	list<CLog*> logs;
	CLog l;

	/*???
	logs = log->selectLogByUserID(1001);
	cout << "?????????" << logs.size() << endl;
	*/


	l.setUserid(1002);
	l.setLogfunction("???");
	l.setLogtype("????");
	l.setDatetime("2025-03-19 16:05:14");
	l.setLoginfo("???????");
	res = log->insertlog(l, "12345678903");
	if (res)
	{
		cout << "??????" << endl;
	}
}
//CRC???????
void demo4()
{

	CRCUtil crcutil;
	// ????????????????????
	CODE_REQ codeReq;
	strcpy(codeReq.phone, "17884878791");
	codeReq.type = 0;

	HEAD head = {};
	char encryptionKey = 0x55;
	//crcutil.encapsulateData(head, codeReq, CODE, 1, encryptionKey);

	// ????????????
	std::cout << "Service Type: " << head.service_type << std::endl;
	std::cout << "Data Length: " << head.data_len << std::endl;
	std::cout << "CRC32: " << head.crc32 << std::endl;
	std::cout << "Client FD: " << head.client_fd << std::endl;
}
//MD5????
void demo5()
{
	MD5 test;
	string a = "";
	cout << "Plain Text: ";
	getline(cin, a);
	cout << "result: " << test.encode(a) << endl;



}
//??????
void demo6()
{
	CPictureModel c;
	CPictrue pictre;
	//??????
	pictre.setPicturename("111");
	pictre.setPicturetime("2025-03-29 14:00:00");
	pictre.setPicturetype(0);
	c.insertPicture(pictre, "12345678903");

}
//?????????
void demo7()
{
	Video video;
	CVideoModel videomodel;
	/*
	strcpy(video.cover_path, "22222");
	strcpy(video.video_name, "11111");
	strcpy(video.video_time,"2025-04-01 12:00:00");
	video.video_current = 11;
	video.video_alltime = 66666;
	strcpy(video.video_starttime, "2025-04-01 13:00:00");
	videomodel.insertNewVideo(video,"12345678901");
	*/

	/*
	vector<string> vectorlist;
	vectorlist = videomodel.SelectMonthList(0,2);
	char datetime[MAX_DATE][20];// ????????ÿÿ?
	for (int i = 0; i < vectorlist.size(); i++)
	{
		//char* str;
		//strcpy(str,vectorlist[i].c_str());
		for (int j = 0; j < vectorlist[i].size(); j++)
		{
			datetime[i][j] = vectorlist[i].c_str()[j];
		}
		datetime[i][vectorlist[i].size()] = '\0';
	}
	for (int i = 0; i < vectorlist.size(); i++)
	{
		cout << "?????????????" << datetime[i] << endl;
	}*/
	char datatime[20] = { "2025-03" };
	cout << strlen(datatime) << endl;
}


int main()
{
	//ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	shmRead* shmR1 = new shmRead(1001, 1002, 1003);
	shmWrite* shmW1 = new shmWrite(2001, 2002, 2003);
	CThreadPool* pool = new CThreadPool(5);
	char data[8192] = { 0 };
	while (true)
	{
		shmR1->read_shm(data);
		HEAD head = {  };
		memcpy(&head, data, sizeof(head));
		cout << "?????????" << head.service_type << endl;
		if (head.service_type == LOGIN)
		{
			CBaseTask* loginTask = new CLoginTask(data, shmW1);
			pool->pushTask(loginTask);
		}
		else if (head.service_type == CODE)
		{
			CBaseTask* codeTask = new CGetodeTask(data, shmW1);
			pool->pushTask(codeTask);
		}
		else if (head.service_type == REGISTER)
		{
			CBaseTask* resTask = new CRegisterTask(data, shmW1);
			pool->pushTask(resTask);
		}
		else if (head.service_type == DOCUMENT)
		{
			CBaseTask* documentTask = new CDocumentTask(data, shmW1);
			pool->pushTask(documentTask);
		}
	
		else if (head.service_type == SEND_PICTURE)
		{
			CBaseTask* captureTask = new CCaptureTask(data, shmW1);
			pool->pushTask(captureTask);
		}
		else if (head.service_type == SEND_VIDEO)
		{
			CBaseTask* sendvideoTask = new CSendVideoTask(data, shmW1);
			pool->pushTask(sendvideoTask);
		}
		else if (head.service_type == GET_VIDEO_LIST)
		{
			CBaseTask* getvideolistTask = new CGetVideoListTask(data, shmW1);
			pool->pushTask(getvideolistTask);
		}
		else if (head.service_type == GET_PICTURE_LIST)
		{
			CBaseTask* getpicturelistTask = new CGetPictureListTask(data, shmW1);
			pool->pushTask(getpicturelistTask);
		}
		else if (head.service_type == GET_OLD_LIST)
		{
			CBaseTask* getoldlistTask = new CGetOldListTask(data, shmW1);
			pool->pushTask(getoldlistTask);
		}
		else if (head.service_type == ELDERINFO)
		{
			CBaseTask* insertTask = new CinsertTask(data, shmW1);
			pool->pushTask(insertTask);
		}
		else if (head.service_type == ELDERINFO_QUERY)
		{
			CBaseTask* queryElderTask = new CQueryElderInfoTask(data, shmW1);
			pool->pushTask(queryElderTask);
		}
		else if (head.service_type == BLOODPRESSURERECORD_QUERY)
		{
			CBaseTask* task = new CQueryBloodPressureTask(data, shmW1);
			pool->pushTask(task);
		}
		else if (head.service_type == MEDICINERECORD_QUERY)
		{
			CBaseTask* task = new CQueryMedicineTask(data, shmW1);
			pool->pushTask(task);
		}
		else if (head.service_type == ACTIVITYRECORD_QUERY)
		{
			CBaseTask* task = new CQueryActivityTask(data, shmW1);
			pool->pushTask(task);
		}
		else if (head.service_type == BLOODPRESSURERECORD)
		{
			CBaseTask* insertTask2= new CinsertTask2(data, shmW1);
			pool->pushTask(insertTask2);
		}
		else if (head.service_type == MEDICINERECORD)
		{
			CBaseTask* insertTask3 = new CinsertTask3(data, shmW1);
			pool->pushTask(insertTask3);
		}
		else if (head.service_type == ACTIVITYRECORD)
		{
			CBaseTask* insertTask4= new CinsertTask4(data, shmW1);
			pool->pushTask(insertTask4);
		}
		else if (head.service_type == CALL_RECORD_REPORT)
		{
			CBaseTask* t = new CCallRecordReportTask(data, shmW1);
			pool->pushTask(t);
		}
		else if (head.service_type == CALL_RECORD_QUERY)
		{
			CBaseTask* t = new CCallRecordQueryTask(data, shmW1);
			pool->pushTask(t);
		}

	}

	//demo8();





	return 0;

}	
