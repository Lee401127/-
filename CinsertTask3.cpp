#include "CinsertTask3.h"

CinsertTask3::CinsertTask3(char* data, shmWrite* p) :CBaseTask(data)
{
    this->p = p;
}

CinsertTask3::~CinsertTask3()
{
}

void CinsertTask3::working()
{
    char sendBuf[8192] = { 0 };
    bzero(sendBuf, sizeof(HEAD) + sizeof(MedicineResp));
    HEAD head = {};
    MedicineReq med_req;
    MedicineResp med_resp;
    bool res;

    memcpy(&head, data, sizeof(HEAD));
    memcpy(&med_req, data + sizeof(HEAD), sizeof(MedicineReq));

    head.data_len = sizeof(MedicineResp);

    // 转换
    MedicineRecord medRecord;
    medRecord.setMedicineName(string(med_req.medRecord.medicineName));
    medRecord.setDosage(string(med_req.medRecord.dosage));
    medRecord.setRecordTime(string(med_req.medRecord.recordTime));
    medRecord.setUsage(string(med_req.medRecord.usage));
    medRecord.setRemark(string(med_req.medRecord.remark));

    CMedicineRecordModel* model = (CMedicineRecordModel*)ModelFactory::getInstance()->getModel(T_MEDICINE);
    if (model == nullptr)
    {
        med_resp.status_code = 1;
        strcpy(med_resp.error_message, "模型获取失败");
        med_resp.record_id = -1;
    }
    else if ((res = model->insertMedicineRecord(medRecord, med_req.phone)) == true)
    {
        cout << "药品记录插入成功" << endl;
        med_resp.status_code = 0;
        med_resp.record_id = 0;
    }
    else
    {
        cout << "药品记录插入失败" << endl;
        med_resp.status_code = 1;
        strcpy(med_resp.error_message, "插入数据库失败");
        med_resp.record_id = -1;
    }

    memcpy(sendBuf, &head, sizeof(HEAD));
    memcpy(sendBuf + sizeof(HEAD), &med_resp, sizeof(MedicineResp));
    p->write_shm(sendBuf);
    bzero(sendBuf, sizeof(HEAD) + sizeof(MedicineResp));
}
