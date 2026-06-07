#include "CGetOldListTask.h"
#include <algorithm>
#include <string>
using std::string;
CGetOldListTask::CGetOldListTask(char* data, shmWrite* p) :CBaseTask(data)
{
	this->p = p;
}

CGetOldListTask::~CGetOldListTask()
{

}

void CGetOldListTask::working()
{
    
    //缓冲�?
    char* sendBuf = new char[8192];
    bzero(sendBuf, sizeof(HEAD) + sizeof(GET_OLDLIST_RESP));
    //验证验证码是否发送成�?
    bool res = false;
    //data是HEAD+CODE_REQ
    //将�?�到的信�?保存到验证码请求

    HEAD head = {  };
    GET_OLDLIST_REQ req = { 0 };
    GET_OLDLIST_RESP resp = { 0 };
    memcpy(&head, data, sizeof(HEAD));
    memcpy(&req, data + sizeof(HEAD), sizeof(GET_OLDLIST_REQ));
    //更改头中的信�?
    head.data_len = sizeof(GET_OLDLIST_RESP);
    int diff = req.to - req.from;
    if (diff <= 0 || diff > MAX_OLD) {
        resp.status_code = 1;
        snprintf(resp.error_message, sizeof(resp.error_message),
            "Invalid range: from=%d, to=%d", req.from, req.to);
    }
    else {
        COldModel* oldModel = (COldModel*)ModelFactory::getInstance()->getModel(T_OLD);
        if (!oldModel) {
            resp.status_code = 2;
            strcpy(resp.error_message, "Model not found");
        }
        else {
            vector<Eld> oldList;
            if (req.family_phone[0] != '\0') {
                oldList = oldModel->getOldListForFamily(req.from, req.to, string(req.family_phone));
                // family_elder �޼�¼����δ��ʱ�����������������Ϊ�գ��˻���ɰ�һ�µ�ȫ�����������б�
                if (oldList.empty()) {
                    oldList = oldModel->getOldList(req.from, req.to);
                }
            }
            else {
                oldList = oldModel->getOldList(req.from, req.to);
            }
            const int actualCount = static_cast<int>(std::min(
                oldList.size(), static_cast<size_t>(MAX_OLD)));
            for (int i = 0; i < actualCount; i++) {
                resp.old_arr[i] = oldList[i];
            }
            // 如果实际数量少于 diff，剩余元素保持为 0（因 resp 已清零）
        }
    }

    // 设置头部长度并写回共�?内存

    memcpy(sendBuf, &head, sizeof(HEAD));
	memcpy(sendBuf + sizeof(HEAD), &resp, sizeof(GET_OLDLIST_RESP));
	p->write_shm(sendBuf);
	bzero(sendBuf, sizeof(HEAD) + sizeof(GET_OLDLIST_RESP));
}
