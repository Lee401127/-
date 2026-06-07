#include "CQueryElderInfoTask.h"

CQueryElderInfoTask::CQueryElderInfoTask(char* data, shmWrite* p) : CBaseTask(data)
{
    this->p = p;
}

CQueryElderInfoTask::~CQueryElderInfoTask()
{
}

void CQueryElderInfoTask::working()
{
    char sendBuf[8192] = { 0 };
    HEAD head = {};
    ElderInfoQueryReq req = {};
    ElderInfoQueryResp resp = {};

    memcpy(&head, data, sizeof(HEAD));
    memcpy(&req, data + sizeof(HEAD), sizeof(ElderInfoQueryReq));
    head.data_len = sizeof(ElderInfoQueryResp);

    CElderInfoModel* model = (CElderInfoModel*)ModelFactory::getInstance()->getModel(T_ELDER);
    if (!model)
    {
        resp.status_code = 2;
        strcpy(resp.error_message, "model not found");
    }
    else
    {
        ElderInfo elderInfo;
        bool found = model->selectCElderInfoByPhone(req.phone, elderInfo);
        if (found)
        {
            resp.status_code = 0;
            resp.elderInfo.age = elderInfo.getAge();
            strncpy(resp.elderInfo.gender, elderInfo.getGender().c_str(), sizeof(resp.elderInfo.gender) - 1);
            strncpy(resp.elderInfo.recordTime, elderInfo.getRecordTime().c_str(), sizeof(resp.elderInfo.recordTime) - 1);
            strncpy(resp.elderInfo.name, elderInfo.getName().c_str(), sizeof(resp.elderInfo.name) - 1);
            strncpy(resp.elderInfo.contact, elderInfo.getContact().c_str(), sizeof(resp.elderInfo.contact) - 1);
            strncpy(resp.elderInfo.remark, elderInfo.getRemark().c_str(), sizeof(resp.elderInfo.remark) - 1);
        }
        else
        {
            resp.status_code = 1;
            strcpy(resp.error_message, "elder info not found");
        }
    }

    memcpy(sendBuf, &head, sizeof(HEAD));
    memcpy(sendBuf + sizeof(HEAD), &resp, sizeof(ElderInfoQueryResp));
    p->write_shm(sendBuf);
}
