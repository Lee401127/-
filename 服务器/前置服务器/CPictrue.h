#pragma once
#include<iostream>
#include<string>

using namespace std;
class CPictrue
{
private:
    int picture_id;
    int user_id;
    string picture_name;
    string picture_time;
    int picture_type;	//0进场  1出场
public:


public:
    int getPictureid() const;
    void setPictureid(int pictureid);

    int getUserid() const;
    void setUserid(int userid);

    string getPicturename() const;
    void setPicturename(string picturename);

    string getPicturetime() const;
    void setPicturetime(string picturetime);

    int getPicturetype() const;
    void setPicturetype(int picturetype);

};
