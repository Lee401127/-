#include "CinsertTask.h"
#include "CLogModel.h"
#include <cstring>

CinsertTask::CinsertTask(char* data, shmWrite* p) :CBaseTask(data)
{
	this->p = p;
}

CinsertTask::~CinsertTask()
{
}

void CinsertTask::working()
{
    char sendBuf[8192] = { 0 };
    bzero(sendBuf, sizeof(HEAD) + sizeof(ElderInfoResp));
    HEAD head = {};
    ElderInfoReq elder_req = {};
    ElderInfoResp elder_resp = {};
    bool res;

    memcpy(&head, data, sizeof(HEAD));
    memcpy(&elder_req, data + sizeof(HEAD), sizeof(ElderInfoReq));

    head.data_len = sizeof(ElderInfoResp);

    auto toSafeString = [](const char* src, size_t maxLen) -> string {
        size_t realLen = 0;
        while (realLen < maxLen && src[realLen] != '\0') {
            ++realLen;
        }
        return string(src, realLen);
    };

    // ?? ElderInfo1 ???? ElderInfo ????
    ElderInfo elderInfo;
    elderInfo.setAge(elder_req.elderInfo.age);
    elderInfo.setGender(toSafeString(elder_req.elderInfo.gender, sizeof(elder_req.elderInfo.gender)));
    elderInfo.setRecordTime(toSafeString(elder_req.elderInfo.recordTime, sizeof(elder_req.elderInfo.recordTime)));
    elderInfo.setName(toSafeString(elder_req.elderInfo.name, sizeof(elder_req.elderInfo.name)));
    elderInfo.setContact(toSafeString(elder_req.elderInfo.contact, sizeof(elder_req.elderInfo.contact)));
    elderInfo.setRemark(toSafeString(elder_req.elderInfo.remark, sizeof(elder_req.elderInfo.remark)));

    CElderInfoModel* model = (CElderInfoModel*)ModelFactory::getInstance()->getModel(T_ELDER);
    if (model == nullptr)
    {
        elder_resp.status_code = 1;
        strcpy(elder_resp.error_message, "model init failed");
        memset(elder_resp.elder_phone, 0, sizeof(elder_resp.elder_phone));
    }
    else if ((res = model->insertCElderInfo(elderInfo, elder_req.phone)) == true)
    {
        cout << "success" << endl;
        // 联系人填「已注册家属」手机号时自动写入 family_elder
        model->syncFamilyElderBinding(string(elder_req.phone), elderInfo.getContact());
        elder_resp.status_code = 0;
        memset(elder_resp.elder_phone, 0, sizeof(elder_resp.elder_phone));
        strncpy(elder_resp.elder_phone, elder_req.phone, sizeof(elder_resp.elder_phone) - 1);
        {
            string rp(elder_req.phone, strnlen(elder_req.phone, sizeof(elder_req.phone)));
            CLogModel* logm = (CLogModel*)ModelFactory::getInstance()->getModel(T_LOG);
            if (logm && !rp.empty())
                logm->quickLogByPhone(rp, "elder_info", "ok", "basic info saved");
        }
    }
    else
    {
        cout << "warn" << endl;
        elder_resp.status_code = 1;
        strcpy(elder_resp.error_message, "insert db failed");
        memset(elder_resp.elder_phone, 0, sizeof(elder_resp.elder_phone));
        {
            string rp(elder_req.phone, strnlen(elder_req.phone, sizeof(elder_req.phone)));
            CLogModel* logm = (CLogModel*)ModelFactory::getInstance()->getModel(T_LOG);
            if (logm && !rp.empty())
                logm->quickLogByPhone(rp, "elder_info", "fail", "basic info insert failed");
        }
    }

    memcpy(sendBuf, &head, sizeof(HEAD));
    memcpy(sendBuf + sizeof(HEAD), &elder_resp, sizeof(ElderInfoResp));
    p->write_shm(sendBuf);
    bzero(sendBuf, sizeof(HEAD) + sizeof(ElderInfoResp));
}

