#pragma once
#include "CBaseTask.h"
class CGetPictureListTask:
 public CBaseTask
{

public:
    CGetPictureListTask(char* data, shmWrite* p);
    ~CGetPictureListTask();
    void working();

private:
    shmWrite* p;    //写到前置服务器



};

