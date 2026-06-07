#pragma once
#include "CBaseTask.h"
class CGetVideoListTask :
    public CBaseTask
{
public:
    CGetVideoListTask(char* data, shmWrite* p);
    ~CGetVideoListTask();
    void working();

private:
    shmWrite* p;    //写到前置服务器



};

