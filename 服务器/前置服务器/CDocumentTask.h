#pragma once
#include "CBaseTask.h"
#include"protecol.h"
#include<map>
#include "CRCUtil.h"
#include<vector>
#include<string>
class CDocumentTask :
    public CBaseTask
{
public:
    CDocumentTask(char* data, shmWrite* p);
    ~CDocumentTask();
    void working();

private:
    shmWrite* p;    //写到前置服务器

    int document_num;  //记录收到包的数量,与请求中对比,如果一致说明可以




    map<int, DOCUMENT_REQ>::iterator it;
    map<string, map<int, DOCUMENT_REQ>>::iterator it2;
    list<DOCUMENT_REQ>::iterator it3;
    CRCUtil crcutil;




};
