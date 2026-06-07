#pragma once
#include "CBaseTask.h"

class CQueryElderInfoTask : public CBaseTask
{
public:
    CQueryElderInfoTask(char* data, shmWrite* p);
    ~CQueryElderInfoTask();
    void working();

private:
    shmWrite* p;
};
