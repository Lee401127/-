#include "CUser.h"
#include "CUser.h"

CUser::CUser()
{
}

CUser::~CUser()
{
}

int CUser::getUserid() const
{
    return user_id;
}

void CUser::setUserid(int userid)
{
    user_id = userid;
}

string CUser::getUserphone() const
{
    return user_phone;
}

void CUser::setUserphone(string userphone)
{
    user_phone = userphone;
}

string CUser::getUsernike() const
{
    return user_nike;
}

void CUser::setUsernike(string usernike)
{
    user_nike = usernike;
}

string CUser::getUserpassword() const
{
    return user_password;
}

void CUser::setUserpassword(string userpassword)
{
    user_password = userpassword;
}

int CUser::getStatus() const
{
    return status;
}

void CUser::setStatus(int status)
{
    this->status = status;
}

int CUser::getKind() const
{
    return kind;
}

void CUser::setKind(int kind)
{
    this->kind = kind;
}

void CUser::to_information()
{
    cout << "ID:" << this->getUserid()
        << "ÊÖ»úºÅÂë:" << this->getUserphone()
        << "êÇ³Æ:" << this->getUsernike()
        << "ÃÜÂë:" << this->getUserpassword()
        <<"ÀàÐÍ"<<this->getKind()
        << "µÇÂ¼×´Ì¬:" << this->getStatus() << endl;
}

