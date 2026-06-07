#include "ActivityRecord.h"

string ActivityRecord::getActivityType() const {
    return activityType;
}

void ActivityRecord::setActivityType(string activityType) {
    this->activityType = activityType;
}

string ActivityRecord::getStartTime() const {
    return startTime;
}

void ActivityRecord::setStartTime(string startTime) {
    this->startTime = startTime;
}

string ActivityRecord::getEndTime() const {
    return endTime;
}

void ActivityRecord::setEndTime(string endTime) {
    this->endTime = endTime;
}

string ActivityRecord::getRemark() const
{
    return remark;
}

void ActivityRecord::setRemark(string remark)
{
    this->remark = remark;
}
