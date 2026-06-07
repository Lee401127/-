#pragma once
#include "CBaseTask.h"
class CinsertTask4 :
    public CBaseTask
{
public:
    CinsertTask4(char* data, shmWrite* p);
    ~CinsertTask4();
    void working();

private:
    shmWrite* p;    //写到前置服务器
};

