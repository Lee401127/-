#include "CPictrue.h"


int CPictrue::getPictureid() const
{
    return picture_id;
}

void CPictrue::setPictureid(int pictureid)
{
    picture_id = pictureid;
}

int CPictrue::getUserid() const
{
    return user_id;
}

void CPictrue::setUserid(int userid)
{
    user_id = userid;
}

string CPictrue::getPicturename() const
{
    return picture_name;
}

void CPictrue::setPicturename(string picturename)
{
    picture_name = picturename;
}

string CPictrue::getPicturetime() const
{
    return picture_time;
}

void CPictrue::setPicturetime(string picturetime)
{
    picture_time = picturetime;
}

int CPictrue::getPicturetype() const
{
    return picture_type;
}

void CPictrue::setPicturetype(int picturetype)
{
    picture_type = picturetype;
}

