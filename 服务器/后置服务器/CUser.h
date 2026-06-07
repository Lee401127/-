#pragma once
#include<iostream>
#include<string>

using namespace std;
//用户实体类
class CUser
{





private:
    int user_id;	//用户id
    string user_phone;	//用户手机号码(账号)
    string user_nike;	//用户昵称
    string user_password;	//用户密码
    int status;	//用户状态
    int kind;//用户类型



public:
    CUser();
    ~CUser();


    int getUserid() const;
    void setUserid(int userid);

    string getUserphone() const;
    void setUserphone(string userphone);

    string getUsernike() const;
    void setUsernike(string usernike);

    string getUserpassword() const;
    void setUserpassword(string userpassword);

    int getStatus() const;
    void setStatus(int status);

    int getKind() const;
    void setKind(int kind);
    //信息显示
    void to_information();

};
