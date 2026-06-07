#include "CinsertTask4.h"

CinsertTask4::CinsertTask4(char* data, shmWrite* p) :CBaseTask(data)
{
    this->p = p;
}

CinsertTask4::~CinsertTask4()
{
}

void CinsertTask4::working()
{
    char sendBuf[8192] = { 0 };
    bzero(sendBuf, sizeof(HEAD) + sizeof(ActivityResp));
    HEAD head = {};
    ActivityReq act_req;
    ActivityResp act_resp;
    bool res;

    memcpy(&head, data, sizeof(HEAD));
    memcpy(&act_req, data + sizeof(HEAD), sizeof(ActivityReq));

    head.data_len = sizeof(ActivityResp);

    // 转换
    ActivityRecord actRecord;
    actRecord.setActivityType(string(act_req.actRecord.activityType));
    actRecord.setStartTime(string(act_req.actRecord.startTime));
    actRecord.setEndTime(string(act_req.actRecord.nendTime)); 


    CActivityRecordModel* model = (CActivityRecordModel*)ModelFactory::getInstance()->getModel(T_ACTIVITY);
    if (model == nullptr)
    {
        act_resp.status_code = 1;
        strcpy(act_resp.error_message, "模型获取失败");
        act_resp.record_id = -1;
    }
    else if ((res = model->insertActivityRecord(actRecord, act_req.phone)) == true)
    {
        cout << "活动记录插入成功" << endl;
        act_resp.status_code = 0;
        act_resp.record_id = 0;
    }
    else
    {
        cout << "活动记录插入失败" << endl;
        act_resp.status_code = 1;
        strcpy(act_resp.error_message, "插入数据库失败");
        act_resp.record_id = -1;
    }

    memcpy(sendBuf, &head, sizeof(HEAD));
    memcpy(sendBuf + sizeof(HEAD), &act_resp, sizeof(ActivityResp));
    p->write_shm(sendBuf);
    bzero(sendBuf, sizeof(HEAD) + sizeof(ActivityResp));
}
