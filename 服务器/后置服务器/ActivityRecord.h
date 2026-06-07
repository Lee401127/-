#pragma once

#include <string>
using namespace std;
class ActivityRecord
{
private:
    string activityType;    // 活动类型
    string startTime;       // 活动开始时间
    string endTime;         // 活动结束时间
    string remark;          // 备注
public:
    string getActivityType() const;
    void setActivityType(string activityType);

    string getStartTime() const;
    void setStartTime(string startTime);

    string getEndTime() const;
    void setEndTime(string endTime);


    string getRemark() const;
    void setRemark(string remark);
};

