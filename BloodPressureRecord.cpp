#include "BloodPressureRecord.h"

int BloodPressureRecord::getSystolic() const {
    return this->systolic;
}

void BloodPressureRecord::setSystolic(int systolic) {
    this->systolic = systolic;
}

int BloodPressureRecord::getDiastolic() const {
    return diastolic;
}

void BloodPressureRecord::setDiastolic(int diastolic) {
    this->diastolic = diastolic;
}

string BloodPressureRecord::getMeasureTime() const {
    return measureTime;
}

void BloodPressureRecord::setMeasureTime(string measureTime) {
    this->measureTime = measureTime;
}

string BloodPressureRecord::getRemark() const {
    return remark;
}

void BloodPressureRecord::setRemark(string remark) {
    this->remark = remark;
}