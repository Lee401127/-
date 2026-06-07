#include "CDocumentTask.h"
#include<fstream>

//??? ?????+???id:????  map<int,DOCUMENT_REQ>:???????????????
static map<string, map<int, DOCUMENT_REQ>> UserdocumentMap;
static map<int, DOCUMENT_REQ> doucumentMap;
bool sorts(const DOCUMENT_REQ& a, const DOCUMENT_REQ& b)
{

    return a.piece_index < b.piece_index;
}



CDocumentTask::CDocumentTask(char* data, shmWrite* p) :CBaseTask(data)
{

    this->p = p;


}

CDocumentTask::~CDocumentTask()
{
}

//map<?????+id,map<int,DOCUMENT_REQ>> documentMap;
void CDocumentTask::working()
{

    cout << "document work" << endl;
    char name[100] = { 0 };    //???????????????
    char name_phone[40] = { 0 };    //????
    string key_first;    //????
    //??????
    char sendbuf[8192] = { 0 };
    bzero(sendbuf, sizeof(HEAD) + sizeof(DOCUMENT_RESP));
    //???
    HEAD head = { };
    DOCUMENT_REQ  document_req = { 0 };
    DOCUMENT_RESP document_resp = { 0 };
    memcpy(&head, data, sizeof(HEAD));
    memcpy(&document_req, data + sizeof(HEAD), sizeof(DOCUMENT_REQ));
    //?????????
    head.data_len = sizeof(DOCUMENT_RESP);
    strcpy(document_resp.document_name, document_req.document_name);
    document_resp.index = document_req.piece_index;
    //???????????
    sprintf(name_phone, "%s%s", document_req.document_name, document_req.phone);
    key_first = name_phone;
    //??????????????????
    //??????????????,??????????????
    auto res = UserdocumentMap[key_first].insert(pair<int, DOCUMENT_REQ>(document_req.piece_index, document_req));
    if (res.second == true)
    {
        cout << "?????????????:" << document_req.document_name << ",???????????:" << document_req.piece_index << endl;

    }
    else//???????(?????????)
    {
        document_resp.status_code = 1;
        strcpy(document_resp.error_message, "????????????????????");
        memcpy(sendbuf, &head, sizeof(HEAD));
        memcpy(sendbuf + sizeof(HEAD), &document_resp, sizeof(DOCUMENT_RESP));
        //p->write_shm(sendbuf);
        bzero(sendbuf, sizeof(HEAD) + sizeof(DOCUMENT_RESP));
    }
    cout << "?????????????:" << document_req.document_name << ",???????????:" << document_req.piece_index << endl;

    //???????????????????????????
    for (it2 = UserdocumentMap.begin(); it2 != UserdocumentMap.end(); it2++)
    {
        cout << "it2 size:" << it2->second.size() << endl;
        //????????????1???,????????????

        if (static_cast<int>(it2->second.size()) == it2->second[0].piece_num)
        {
            cout << it2->first << ":?????????" << endl;
            list<DOCUMENT_REQ> mylist;
            //??????????list?????????
            for (this->it = it2->second.begin(); this->it != it2->second.end(); this->it++)
            {
                mylist.push_back(this->it->second);
            }
            //????????
            mylist.sort(sorts);
            cout << "document_size:" << mylist.front().document_size << endl;
            //??????????????(????????????)
            bzero(name, sizeof(name));
            sprintf(name, "%s%s%s", it2->second[0].document_name, ".", it2->second[0].document_type);
            ofstream outfile(name, std::ios::binary | std::ios::app);
            if (outfile.is_open())
            {
                for (this->it3 = mylist.begin(); this->it3 != mylist.end(); this->it3++)
                {
                    cout << "it3->piece_index:" << this->it3->piece_index << endl;
                    outfile.write(this->it3->piece_data, this->it3->piece_size);
                }
                outfile.close();
                cout << "??????????????" << endl;
                //???????????????(?????????????????)
                UserdocumentMap.erase(it2->first);
                //??????
                document_resp.status_code = 0;
                memcpy(sendbuf, &head, sizeof(HEAD));
                memcpy(sendbuf + sizeof(HEAD), &document_resp, sizeof(DOCUMENT_RESP));
                //p->write_shm(sendbuf);
                bzero(sendbuf, sizeof(HEAD) + sizeof(DOCUMENT_RESP));
            }
            else
            {

                cerr << "????????????" << endl;
            }
            mylist.clear();

        }

    }

}
