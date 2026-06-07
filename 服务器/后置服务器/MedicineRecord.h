#pragma once
#include <string>
using namespace std;
class MedicineRecord
{
private:
    string medicineName;    // 药品名称
    string dosage;          // 剂量
    string recordTime;      // 记录时间
    string usage;           // 用法
    string remark;          // 备注

public:
    string getMedicineName() const;
    void setMedicineName(string medicineName);

    string getDosage() const;
    void setDosage(string dosage);

    string getRecordTime() const;
    void setRecordTime(string recordTime);

    string getUsage() const;
    void setUsage(string usage);

    string getRemark() const;
    void setRemark(string remark);
};

