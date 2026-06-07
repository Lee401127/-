#pragma once
#include <unistd.h>
#include <map>
#include "CBaseTask.h"
#include "protecol.h"
#include "CRegisterTask.h"

#include "MD5.h"
#include"CRCUtil.h"
class CRegisterTask :
    public CBaseTask
{
public:
    CRegisterTask(char* data, shmWrite* p);
    ~CRegisterTask();
    void working();

private:
    shmWrite* p;    //写到前置服务器
    MD5 test;       //MD5加密算法
    CRCUtil crc;
};

