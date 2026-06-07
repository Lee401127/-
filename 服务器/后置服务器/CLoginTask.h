#pragma once
#include <unistd.h>
#include <map>
#include "CBaseTask.h"
#include "protecol.h"
#include"CRCUtil.h"
class CLoginTask :
    public CBaseTask
{
public:
    //char* data获取到的数据
    CLoginTask(char* data, shmWrite* p);
    ~CLoginTask();
    void working();

private:
    shmWrite* p;    //写到前置服务器
    CRCUtil crc;
    vector<string>::iterator it1;
};
