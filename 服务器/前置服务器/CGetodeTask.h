#pragma once
#include "CBaseTask.h"
#include"protecol.h"
#include "getCodeUtil.h"
#include"CRCUtil.h"
class CGetodeTask :
    public CBaseTask
{

public:
    CGetodeTask(char* data, shmWrite* p);
    ~CGetodeTask();
    void working();


private:

    shmWrite* p;//写到前置服务器
    getCodeUtil* getcode;   //短信验证码
    char* code;   //验证码
    CRCUtil crc;
};

