#pragma once
#include <string>
using namespace std;
class ElderInfo
{
private:
    int age;                // 年龄
    string gender;          // 性别
    string recordTime;      // 记录时间
    string name;            // 姓名
    string contact;         // 联系人
    string remark;          // 备注

public:
    int getAge() const;
    void setAge(int age);

    string getGender() const;
    void setGender(string gender);

    string getRecordTime() const;
    void setRecordTime(string recordTime);

    string getName() const;
    void setName(string name);

    string getContact() const;
    void setContact(string contact);

    string getRemark() const;
    void setRemark(string remark);
};

