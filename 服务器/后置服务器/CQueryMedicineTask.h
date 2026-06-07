#pragma once
#include "CBaseTask.h"

class CQueryMedicineTask : public CBaseTask
{
public:
    CQueryMedicineTask(char* data, shmWrite* p);
    ~CQueryMedicineTask();
    void working();

private:
    shmWrite* p;
};
