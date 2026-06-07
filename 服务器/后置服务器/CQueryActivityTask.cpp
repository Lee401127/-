#include "CQueryActivityTask.h"

CQueryActivityTask::CQueryActivityTask(char* data, shmWrite* p) : CBaseTask(data)
{
    this->p = p;
}

CQueryActivityTask::~CQueryActivityTask()
{
}

void CQueryActivityTask::working()
{
    char sendBuf[8192] = { 0 };
    HEAD head = {};
    ActivityQueryReq req = {};
    ActivityQueryResp resp = {};

    memcpy(&head, data, sizeof(HEAD));
    memcpy(&req, data + sizeof(HEAD), sizeof(ActivityQueryReq));
    head.data_len = sizeof(ActivityQueryResp);

    CActivityRecordModel* model = (CActivityRecordModel*)ModelFactory::getInstance()->getModel(T_ACTIVITY);
    if (!model)
    {
        resp.status_code = 2;
        strcpy(resp.error_message, "model not found");
    }
    else
    {
        vector<ActivityRecord1> list = model->selectByPhone(req.phone);
        if (list.empty())
        {
            resp.status_code = 1;
            strcpy(resp.error_message, "activity record not found");
        }
        else
        {
            resp.status_code = 0;
            int n = (int)list.size();
            if (n > MAX_OLD) n = MAX_OLD;
            for (int i = 0; i < n; ++i) resp.records[i] = list[i];
        }
    }

    memcpy(sendBuf, &head, sizeof(HEAD));
    memcpy(sendBuf + sizeof(HEAD), &resp, sizeof(ActivityQueryResp));
    p->write_shm(sendBuf);
}
