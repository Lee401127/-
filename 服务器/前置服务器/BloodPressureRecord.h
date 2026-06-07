#pragma once
#include <string>
using namespace std;
class BloodPressureRecord
{
private:
    int systolic;           // 收缩压
    int diastolic;          // 舒张压
    string measureTime;     // 测量时间
    string remark;          // 备注

public:
    int getSystolic() const;
    void setSystolic(int systolic);

    int getDiastolic() const;
    void setDiastolic(int diastolic);

    string getMeasureTime() const;
    void setMeasureTime(string measureTime);

    string getRemark() const;
    void setRemark(string remark);
};

