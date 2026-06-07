
#include "CLoginTask.h"
#include "ModelFactory.h"
#include "IdentityMap.h"
#include "CLogModel.h"
#include <cstring>
#include <string>

extern char* ismycode;
static vector<string> online_user;

CLoginTask::CLoginTask(char* data, shmWrite* p) : CBaseTask(data)
{
	this->p = p;
}

CLoginTask::~CLoginTask()
{
}

void CLoginTask::working()
{
	char* sendBuf = new char[8192];
	bzero(sendBuf, sizeof(HEAD) + sizeof(LOGIN_RESP));
	HEAD head = {};
	memcpy(&head, data, sizeof(HEAD));
	LOGIN_REQ login_req = { 0 };
	LOGIN_RESP login_resp = { 0 };
	head.data_len = sizeof(LOGIN_RESP);
	memcpy(&login_req, data + sizeof(HEAD), sizeof(LOGIN_REQ));
	cout << "?????:" << login_req.phone << endl;

	CUserModel* cusermodel = (CUserModel*)ModelFactory::getInstance()->getModel(T_USER);
	const std::string phoneStr(login_req.phone, strnlen(login_req.phone, sizeof(login_req.phone)));
	const std::string pwdStr(login_req.password, strnlen(login_req.password, sizeof(login_req.password)));
	const int identity = cusermodel->getIdentityIfPasswordOk(phoneStr, pwdStr);
	const int expectedIdentity = protocolKindToDbIdentity(login_req.kind);

	bool already_online = false;
	for (this->it1 = online_user.begin(); this->it1 != online_user.end(); ++this->it1)
	{
		if (strcmp(login_req.phone, (*this->it1).c_str()) == 0)
		{
			already_online = true;
			strcpy(login_resp.phone, login_req.phone);
			login_resp.status_code = 1;
			strcpy(login_resp.error_message, "the account is using");
			break;
		}
	}

	if (!already_online)
	{
		if (strcmp(ismycode, login_req.code) != 0)
		{
			strcpy(login_resp.phone, login_req.phone);
			login_resp.status_code = 3;
			strcpy(login_resp.error_message, "????????????");
		}
		else if (identity < 0)
		{
			strcpy(login_resp.phone, login_req.phone);
			login_resp.status_code = 1;
			strcpy(login_resp.error_message, "using name or passworf is warning ");
		}
		else if (expectedIdentity < 0)
		{
			strcpy(login_resp.phone, login_req.phone);
			login_resp.status_code = 6;
			login_resp.error_message[0] = '\0';
		}
		else if (identity != expectedIdentity)
		{
			strcpy(login_resp.phone, login_req.phone);
			login_resp.status_code = 6;
			login_resp.error_message[0] = '\0';
		}
		else
		{
			strcpy(login_resp.phone, login_req.phone);
			if (login_req.kind == 0)
				login_resp.status_code = 0;
			else if (login_req.kind == 1)
				login_resp.status_code = 4;
			else if (login_req.kind == 2)
				login_resp.status_code = 5;
			online_user.push_back(string(login_req.phone));
			cout << "login_resp.phone" << login_resp.phone << endl;
			cout << "login_req.phone" << login_req.phone << endl;
		}
	}

	CLogModel* logm = (CLogModel*)ModelFactory::getInstance()->getModel(T_LOG);
	if (logm && !phoneStr.empty()) {
		if (already_online)
			logm->quickLogByPhone(phoneStr, "login", "fail", "already online");
		else if (login_resp.status_code == 0)
			logm->quickLogByPhone(phoneStr, "login", "ok", "elder client");
		else if (login_resp.status_code == 4)
			logm->quickLogByPhone(phoneStr, "login", "ok", "caregiver client");
		else if (login_resp.status_code == 5)
			logm->quickLogByPhone(phoneStr, "login", "ok", "family client");
		else if (login_resp.status_code == 3)
			logm->quickLogByPhone(phoneStr, "login", "fail", "bad sms code");
		else if (login_resp.status_code == 6)
			logm->quickLogByPhone(phoneStr, "login", "fail", "role mismatch");
		else if (login_resp.status_code == 1)
			logm->quickLogByPhone(phoneStr, "login", "fail", "bad account or password");
	}

	memcpy(sendBuf, &head, sizeof(HEAD));
	memcpy(sendBuf + sizeof(HEAD), &login_resp, sizeof(LOGIN_RESP));
	p->write_shm(sendBuf);
	bzero(sendBuf, sizeof(HEAD) + sizeof(LOGIN_RESP));
	delete[] sendBuf;
}
