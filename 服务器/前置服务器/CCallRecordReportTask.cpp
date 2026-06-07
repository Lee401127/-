#include "CCallRecordReportTask.h"
#include "CCallRecordModel.h"
#include "protecol.h"
#include "CLogModel.h"
#include "CLog.h"
#include "ModelFactory.h"
#include <cstring>
#include <ctime>

CCallRecordReportTask::CCallRecordReportTask(char* data, shmWrite* p) : CBaseTask(data)
{
	this->p = p;
}

CCallRecordReportTask::~CCallRecordReportTask() {}

void CCallRecordReportTask::working()
{
	char sendBuf[8192] = { 0 };
	HEAD head = {};
	CALL_RECORD_REPORT_REQ req = {};
	CALL_RECORD_REPORT_RESP resp = { 0 };

	memcpy(&head, data, sizeof(HEAD));
	memcpy(&req, data + sizeof(HEAD), sizeof(CALL_RECORD_REPORT_REQ));
	head.data_len = sizeof(CALL_RECORD_REPORT_RESP);

	if (strlen(req.elder_phone) == 0) {
		resp.status_code = 1;
		strcpy(resp.error_message, "elder phone empty");
	}
	else {
		CCallRecordModel model;
		int newId = 0;
		string remark(req.remark);
		bool ok = model.insertCall(string(req.elder_phone), req.call_type, remark, &newId);
		if (ok) {
			resp.status_code = 0;
			resp.call_id = newId;
			CLogModel* logModel = (CLogModel*)ModelFactory::getInstance()->getModel(T_LOG);
			if (logModel) {
				CLog l;
				l.setLogfunction("呼叫");
				l.setLogtype("上报");
				char tbuf[32] = { 0 };
				time_t now = time(nullptr);
				struct tm tm_buf;
				localtime_r(&now, &tm_buf);
				strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S", &tm_buf);
				l.setDatetime(string(tbuf));
				l.setLoginfo("老人发起呼叫");
				logModel->insertlog(l, string(req.elder_phone));
			}
		}
		else {
			resp.status_code = 1;
			strcpy(resp.error_message, "insert call_record failed");
		}
	}

	memcpy(sendBuf, &head, sizeof(HEAD));
	memcpy(sendBuf + sizeof(HEAD), &resp, sizeof(CALL_RECORD_REPORT_RESP));
	p->write_shm(sendBuf);
}
