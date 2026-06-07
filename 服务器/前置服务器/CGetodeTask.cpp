#include "CGetodeTask.h"
#include "ModelFactory.h"
#include "CLogModel.h"
#include <cstring>
#include <string>
using std::string;
char* ismycode = new char[7];
CGetodeTask::CGetodeTask(char* data, shmWrite* p) :CBaseTask(data)
{

	this->p = p;
	this->code = new char[7];

}

CGetodeTask::~CGetodeTask()
{
}

void CGetodeTask::working()
{
	//??????
	char* sendBuf = new char[8192];
	bzero(sendBuf, sizeof(HEAD) + sizeof(CODE_RESP));
	//???????????????
	bool res = false;
	//data??HEAD+CODE_REQ
	//?????????????????????????

	HEAD head = {  };
	CODE_RESP code_resp = { 0 };
	CODE_REQ code_req = { 0 };
	memcpy(&head, data, sizeof(HEAD));
	head.data_len = sizeof(CODE_RESP);
	memcpy(&code_req, data + sizeof(HEAD), sizeof(CODE_REQ));
	//????????????? 0:????  1:???
	if (code_req.type == 0)
	{
		this->getcode = new getCodeUtil(code_req.phone);
		res = this->getcode->isSend();
		if (res == true)
		{
			this->code = this->getcode->getCode();
			strcpy(code_resp.phone, code_req.phone);
			code_resp.status_code = 0;
			strcpy(code_resp.code, this->code);
			strcpy(ismycode, this->code);
			cout << "????????????,???????????:" << this->code << endl;
			{
				string rp(code_req.phone, strnlen(code_req.phone, sizeof(code_req.phone)));
				CLogModel* logm = (CLogModel*)ModelFactory::getInstance()->getModel(T_LOG);
				if (logm && !rp.empty())
					logm->quickLogByPhone(rp, "sms_code", "ok", "sms verification code sent");
			}
		}
		else if (res == false)
		{
			strcpy(code_resp.phone, code_req.phone);
			code_resp.status_code = 1;
			strcpy(code_resp.error_message, "??????????,??????????????????");
			{
				string rp(code_req.phone, strnlen(code_req.phone, sizeof(code_req.phone)));
				CLogModel* logm = (CLogModel*)ModelFactory::getInstance()->getModel(T_LOG);
				if (logm && !rp.empty())
					logm->quickLogByPhone(rp, "sms_code", "fail", "sms send failed");
			}
		}
	}
	else if (code_req.type == 1)
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		for (int i = 0; i < 6; ++i)
		{
			this->code[i] = static_cast<char>((rand() % 10) + '0');
			this->code[6] = '\0';
		}
		//strcpy(code_resp.phone, code_req.phone);
		code_resp.status_code = 0;
		strcpy(code_resp.code, this->code);
		strcpy(ismycode, this->code);
		cout << "????????????,???????????:" << this->code << endl;
		{
			string rp(code_req.phone, strnlen(code_req.phone, sizeof(code_req.phone)));
			CLogModel* logm = (CLogModel*)ModelFactory::getInstance()->getModel(T_LOG);
			if (logm && !rp.empty())
				logm->quickLogByPhone(rp, "captcha", "ok", "image captcha generated");
		}
	}
	memcpy(sendBuf, &head, sizeof(HEAD));
	memcpy(sendBuf + sizeof(HEAD), &code_resp, sizeof(CODE_RESP));
	this->p->write_shm(sendBuf);
	//???sendBuf
	bzero(sendBuf, sizeof(HEAD) + sizeof(CODE_RESP));



}
