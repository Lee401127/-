#include "CinsertTask2.h"


CinsertTask2::CinsertTask2(char* data, shmWrite* p) :CBaseTask(data)
{
    this->p = p;
}

CinsertTask2::~CinsertTask2()
{
}

void CinsertTask2::working()
{
    char sendBuf[8192] = { 0 };
    bzero(sendBuf, sizeof(HEAD) + sizeof(BloodPressureResp));
    HEAD head = {};
    BloodPressureReq bp_req;
    BloodPressureResp bp_resp;
    bool res;

    memcpy(&head, data, sizeof(HEAD));
    memcpy(&bp_req, data + sizeof(HEAD), sizeof(BloodPressureReq));

    head.data_len = sizeof(BloodPressureResp);

    // ×ª»»
    BloodPressureRecord bpRecord;
    bpRecord.setSystolic(bp_req.bpRecord.systolic);
    bpRecord.setDiastolic(bp_req.bpRecord.diastolic);
    bpRecord.setMeasureTime(string(bp_req.bpRecord.measureTime));
    bpRecord.setRemark(string(bp_req.bpRecord.remark));

    CBloodPressureRecordModel* model = (CBloodPressureRecordModel*)ModelFactory::getInstance()->getModel(T_BLOOD);
    if (model == nullptr)
    {
        bp_resp.status_code = 1;
        strcpy(bp_resp.error_message, "模型获取失败");
        bp_resp.record_id = -1;
    }
    else if ((res = model->insertBloodPressureRecord(bpRecord, bp_req.phone)) == true)
    {
        cout << "ÑªÑ¹¼ÇÂ¼²åÈë³É¹¦" << endl;
        bp_resp.status_code = 0;
        bp_resp.record_id = 0;
    }
    else
    {
        cout << "ÑªÑ¹¼ÇÂ¼²åÈëÊ§°Ü" << endl;
        bp_resp.status_code = 1;
        strcpy(bp_resp.error_message, "²åÈëÊý¾Ý¿âÊ§°Ü");
        bp_resp.record_id = -1;
    }

    memcpy(sendBuf, &head, sizeof(HEAD));
    memcpy(sendBuf + sizeof(HEAD), &bp_resp, sizeof(BloodPressureResp));
    p->write_shm(sendBuf);
    bzero(sendBuf, sizeof(HEAD) + sizeof(BloodPressureResp));
}

