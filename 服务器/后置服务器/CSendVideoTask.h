#pragma once
#include "CBaseTask.h"

class CSendVideoTask :
    public CBaseTask
{
public:
    CSendVideoTask(char* data, shmWrite* p);
    ~CSendVideoTask();
    void working();

private:
    shmWrite* p;    //写到前置服务器





};
