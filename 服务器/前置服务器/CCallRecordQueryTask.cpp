#include "CCallRecordQueryTask.h"
#include "CCallRecordModel.h"
#include "protecol.h"
#include <cstring>
#include <vector>
using std::vector;

CCallRecordQueryTask::CCallRecordQueryTask(char* data, shmWrite* p) : CBaseTask(data)
{
	this->p = p;
}

CCallRecordQueryTask::~CCallRecordQueryTask() {}

void CCallRecordQueryTask::working()
{
	char sendBuf[8192] = { 0 };
	HEAD head = {};
	CALL_RECORD_QUERY_REQ req = {};
	CALL_RECORD_QUERY_RESP resp = { 0 };

	memcpy(&head, data, sizeof(HEAD));
	memcpy(&req, data + sizeof(HEAD), sizeof(CALL_RECORD_QUERY_REQ));
	head.data_len = sizeof(CALL_RECORD_QUERY_RESP);

	int diff = req.to - req.from;
	if (strlen(req.family_phone) == 0 || strlen(req.elder_phone) == 0 || diff <= 0 || diff > MAX_CALL_RECORD) {
		resp.status_code = 1;
		snprintf(resp.error_message, sizeof(resp.error_message), "invalid query range or phone");
	}
	else {
		CCallRecordModel model;
		vector<CallRecordEntity> rows;
		if (!model.selectForRequester(string(req.family_phone), string(req.elder_phone), req.from, req.to, rows)) {
			resp.status_code = 1;
			strcpy(resp.error_message, "query failed");
		}
		else {
			resp.status_code = 0;
			int n = (int)rows.size();
			if (n > MAX_CALL_RECORD) n = MAX_CALL_RECORD;
			resp.record_count = n;
			for (int i = 0; i < n; i++) {
				resp.records[i].call_id = rows[i].call_id;
				strncpy(resp.records[i].elder_phone, rows[i].elder_phone.c_str(), sizeof(resp.records[i].elder_phone) - 1);
				resp.records[i].elder_phone[sizeof(resp.records[i].elder_phone) - 1] = '\0';
				resp.records[i].call_type = rows[i].call_type;
				strncpy(resp.records[i].call_time, rows[i].call_time.c_str(), sizeof(resp.records[i].call_time) - 1);
				resp.records[i].call_time[sizeof(resp.records[i].call_time) - 1] = '\0';
				strncpy(resp.records[i].remark, rows[i].remark.c_str(), sizeof(resp.records[i].remark) - 1);
				resp.records[i].remark[sizeof(resp.records[i].remark) - 1] = '\0';
			}
		}
	}

	memcpy(sendBuf, &head, sizeof(HEAD));
	memcpy(sendBuf + sizeof(HEAD), &resp, sizeof(CALL_RECORD_QUERY_RESP));
	p->write_shm(sendBuf);
}
