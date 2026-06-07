#pragma once
#include "CBaseTask.h"
class CinsertTask :
    public CBaseTask
{
public:
    CinsertTask(char* data, shmWrite* p);
    ~CinsertTask();
    void working();

private:
    shmWrite* p;    //写到前置服务器
};

