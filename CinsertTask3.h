#pragma once
#include "CBaseTask.h"
class CinsertTask3 :
    public CBaseTask
{
public:
    CinsertTask3(char* data, shmWrite* p);
    ~CinsertTask3();
    void working();

private:
    shmWrite* p;    //写到前置服务器
};

