#include "CBaseTask.h"
#pragma once
class CGetOldListTask :public CBaseTask
{
public:
    CGetOldListTask(char* data, shmWrite* p);
    ~CGetOldListTask();
    void working();

private:
    shmWrite* p;    //写到前置服务器
};

