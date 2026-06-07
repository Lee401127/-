#pragma once
#include "CBaseTask.h"

class CQueryBloodPressureTask : public CBaseTask
{
public:
    CQueryBloodPressureTask(char* data, shmWrite* p);
    ~CQueryBloodPressureTask();
    void working();

private:
    shmWrite* p;
};
