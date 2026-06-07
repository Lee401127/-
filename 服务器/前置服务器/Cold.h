#pragma once
#include<iostream>
#include<string>

using namespace std;
class Cold
{

private:
    int elder_id;   //老人id
    string user_phone;	//用户手机号码(账号)




public:


    int getElderid() const;
    void setElderid(int elderid);
    string getUserphone() const;
    void setUserphone(string userphone);


};

