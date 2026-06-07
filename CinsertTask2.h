#pragma once
#include "CBaseTask.h"
class CinsertTask2 :
    public CBaseTask
{
public:
    CinsertTask2(char* data, shmWrite* p);
    ~CinsertTask2();
    void working();

private:
    shmWrite* p;    //写到前置服务器
};

