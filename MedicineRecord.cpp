#include "MedicineRecord.h"

string MedicineRecord::getMedicineName() const {
    return medicineName;
}

void MedicineRecord::setMedicineName(string medicineName) {
    this->medicineName = medicineName;
}

string MedicineRecord::getDosage() const {
    return dosage;
}

void MedicineRecord::setDosage(string dosage) {
    this->dosage = dosage;
}

string MedicineRecord::getRecordTime() const {
    return recordTime;
}

void MedicineRecord::setRecordTime(string recordTime) {
    this->recordTime = recordTime;
}

string MedicineRecord::getUsage() const {
    return usage;
}

void MedicineRecord::setUsage(string usage) {
    this->usage = usage;
}

string MedicineRecord::getRemark() const {
    return remark;
}

void MedicineRecord::setRemark(string remark) {
    this->remark = remark;
}