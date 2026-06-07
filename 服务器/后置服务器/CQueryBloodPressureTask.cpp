#include "CQueryBloodPressureTask.h"

CQueryBloodPressureTask::CQueryBloodPressureTask(char* data, shmWrite* p) : CBaseTask(data)
{
    this->p = p;
}

CQueryBloodPressureTask::~CQueryBloodPressureTask()
{
}

void CQueryBloodPressureTask::working()
{
    char sendBuf[8192] = { 0 };
    HEAD head = {};
    BloodPressureQueryReq req = {};
    BloodPressureQueryResp resp = {};

    memcpy(&head, data, sizeof(HEAD));
    memcpy(&req, data + sizeof(HEAD), sizeof(BloodPressureQueryReq));
    head.data_len = sizeof(BloodPressureQueryResp);

    CBloodPressureRecordModel* model = (CBloodPressureRecordModel*)ModelFactory::getInstance()->getModel(T_BLOOD);
    if (!model)
    {
        resp.status_code = 2;
        strcpy(resp.error_message, "model not found");
    }
    else
    {
        vector<BloodPressureRecord1> list = model->selectByPhone(req.phone);
        if (list.empty())
        {
            resp.status_code = 1;
            strcpy(resp.error_message, "blood pressure not found");
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
    memcpy(sendBuf + sizeof(HEAD), &resp, sizeof(BloodPressureQueryResp));
    p->write_shm(sendBuf);
}
