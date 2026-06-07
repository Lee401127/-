#include "CQueryMedicineTask.h"

CQueryMedicineTask::CQueryMedicineTask(char* data, shmWrite* p) : CBaseTask(data)
{
    this->p = p;
}

CQueryMedicineTask::~CQueryMedicineTask()
{
}

void CQueryMedicineTask::working()
{
    char sendBuf[8192] = { 0 };
    HEAD head = {};
    MedicineQueryReq req = {};
    MedicineQueryResp resp = {};

    memcpy(&head, data, sizeof(HEAD));
    memcpy(&req, data + sizeof(HEAD), sizeof(MedicineQueryReq));
    head.data_len = sizeof(MedicineQueryResp);

    CMedicineRecordModel* model = (CMedicineRecordModel*)ModelFactory::getInstance()->getModel(T_MEDICINE);
    if (!model)
    {
        resp.status_code = 2;
        strcpy(resp.error_message, "model not found");
    }
    else
    {
        vector<MedicineRecord1> list = model->selectByPhone(req.phone);
        if (list.empty())
        {
            resp.status_code = 1;
            strcpy(resp.error_message, "medicine record not found");
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
    memcpy(sendBuf + sizeof(HEAD), &resp, sizeof(MedicineQueryResp));
    p->write_shm(sendBuf);
}
