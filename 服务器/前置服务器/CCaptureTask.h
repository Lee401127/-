#pragma once
#include "CBaseTask.h"
class CCaptureTask :
    public CBaseTask
{
public:
    CCaptureTask(char* data, shmWrite* p);
    ~CCaptureTask();
    void working();


private:
    shmWrite* p;

};

