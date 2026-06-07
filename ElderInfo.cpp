#include "ElderInfo.h"

int ElderInfo::getAge() const {
    return this->age;
}

void ElderInfo::setAge(int age) {
    this->age = age;
}

string ElderInfo::getGender() const {
    return gender;
}

void ElderInfo::setGender(string gender) {
    this->gender = gender;
}

string ElderInfo::getRecordTime() const {
    return recordTime;
}

void ElderInfo::setRecordTime(string recordTime) {
    this->recordTime = recordTime;
}

string ElderInfo::getName() const {
    return name;
}

void ElderInfo::setName(string name) {
    this->name = name;
}

string ElderInfo::getContact() const {
    return contact;
}

void ElderInfo::setContact(string contact) {
    this->contact = contact;
}

string ElderInfo::getRemark() const {
    return remark;
}

void ElderInfo::setRemark(string remark) {
    this->remark = remark;
}