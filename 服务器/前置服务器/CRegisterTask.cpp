#include "CRegisterTask.h"
#include "IdentityMap.h"
#include "ModelFactory.h"
#include "CLogModel.h"
#include <cstring>

extern char* ismycode;
CRegisterTask::CRegisterTask(char* data, shmWrite* p) :CBaseTask(data)
{
    this->p = p;
}

CRegisterTask::~CRegisterTask()
{
}

void CRegisterTask::working()
{
    char encryptionKey = 0x55;
    //????????
    bool res = false;
    //????
    char* password = new char[7];
    //??????
    list<CUser*> userlist;
    CUser user;
    //??????
    char* sendBuf = new char[8192];
    bzero(sendBuf, sizeof(HEAD) + sizeof(REGISTER_RESP));
    //?????
    HEAD head = {  };
    memcpy(&head, data, sizeof(HEAD));
    head.data_len = sizeof(REGISTER_RESP);
    //???????
    REGISTER_REQ register_req = { 0 };
    REGISTER_RESP register_resp = { 0 };
    //???????????
    memcpy(&register_req, data + sizeof(HEAD), sizeof(REGISTER_REQ));
    //???????????????
    CUserModel* cusermodel = (CUserModel*)ModelFactory::getInstance()->getModel(T_USER);
    userlist = cusermodel->selectByPhone(register_req.phone);


    //0???????????????????
    //1???????????????????
    if (userlist.size() > 0)//??????????????????
    {
        register_resp.status_code = 1;
        strcpy(register_resp.phone, register_req.phone);
        strcpy(register_resp.error_message, "??????????");
        {
            string rp(register_req.phone, strnlen(register_req.phone, sizeof(register_req.phone)));
            CLogModel* logm = (CLogModel*)ModelFactory::getInstance()->getModel(T_LOG);
            if (logm && !rp.empty())
                logm->quickLogByPhone(rp, "register", "fail", "phone already exists");
        }
    }
    else
    {
        cout<<"code"<<ismycode<<"your code"<<register_req.code << endl;

        if (strcmp(ismycode, register_req.code) == 0)//???????????
        {
            srand(static_cast<unsigned int>(time(nullptr)));
            for (int i = 0; i < 6; ++i)
            {
                password[i] = static_cast<char>((rand() % 10) + '0');
                password[6] = '\0';
            }
            register_resp.status_code = 0;
            strcpy(register_resp.phone, register_req.phone);
            strcpy(register_resp.password, password);
            //???MD5??????????
            string enpassword = this->test.encode(password);

            //???????????????
            user.setUsernike(register_req.phone);
            //user.setStatus(0);
            user.setUserpassword(enpassword);
            user.setUserphone(register_req.phone);
            const int dbIdentity = protocolKindToDbIdentity(register_req.kind);
            if (dbIdentity < 0) {
                register_resp.status_code = 1;
                strcpy(register_resp.phone, register_req.phone);
                strcpy(register_resp.error_message, "invalid role kind");
                {
                    string rp(register_req.phone, strnlen(register_req.phone, sizeof(register_req.phone)));
                    CLogModel* logm = (CLogModel*)ModelFactory::getInstance()->getModel(T_LOG);
                    if (logm && !rp.empty())
                        logm->quickLogByPhone(rp, "register", "fail", "invalid role kind");
                }
            } else {
            user.setKind(dbIdentity);
            res = cusermodel->insertUser(user);
            if (res > 0)
            {
                cout << "?????????" << endl;
                cout << "?????????????????" << endl;
            }
            else
            {
                string rp(register_req.phone, strnlen(register_req.phone, sizeof(register_req.phone)));
                CLogModel* logm = (CLogModel*)ModelFactory::getInstance()->getModel(T_LOG);
                if (logm && !rp.empty())
                    logm->quickLogByPhone(rp, "register", "fail", "insert user failed");
            }
            // ???? kind==0 ???? elder ?????????????? =1 ?????????? elder
            if (register_req.kind == 0)
            {
                COldModel* coldmodel = (COldModel*)ModelFactory::getInstance()->getModel(T_OLD);
                Cold cold;

                cold.setUserphone(register_req.phone);
                bool elderRes = coldmodel->insertUser(cold);
                if (elderRes)
                {
                    cout << "????????????" << endl;
                }
                else
                {
                    cout << "????????????" << endl;
                }
            }
            if (register_resp.status_code == 0 && res) {
                string rp(register_req.phone, strnlen(register_req.phone, sizeof(register_req.phone)));
                CLogModel* logm = (CLogModel*)ModelFactory::getInstance()->getModel(T_LOG);
                if (logm && !rp.empty()) {
                    const char* role = "family";
                    if (register_req.kind == 0) role = "elder";
                    else if (register_req.kind == 1) role = "caregiver";
                    logm->quickLogByPhone(rp, "register", "ok", string("registered as ") + role);
                }
            }
            }
        }
        else
        {
            register_resp.status_code = 1;
            strcpy(register_resp.phone, register_req.phone);
            strcpy(register_resp.error_message, "????????");
            {
                string rp(register_req.phone, strnlen(register_req.phone, sizeof(register_req.phone)));
                CLogModel* logm = (CLogModel*)ModelFactory::getInstance()->getModel(T_LOG);
                if (logm && !rp.empty())
                    logm->quickLogByPhone(rp, "register", "fail", "bad sms code");
            }
        }

    }
    //???????
    //????????????????
    memcpy(sendBuf, &head, sizeof(HEAD));
    memcpy(sendBuf + sizeof(HEAD), &register_resp, sizeof(REGISTER_RESP));
    p->write_shm(sendBuf);
    bzero(sendBuf, sizeof(HEAD) + sizeof(REGISTER_RESP));

}
















