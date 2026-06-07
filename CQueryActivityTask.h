#pragma once
#include "CBaseTask.h"

class CQueryActivityTask : public CBaseTask
{
public:
    CQueryActivityTask(char* data, shmWrite* p);
    ~CQueryActivityTask();
    void working();

private:
    shmWrite* p;
};
