#include "CVideo.h"

int CVideo::getVideoid() const
{
    return video_id;
}

void CVideo::setVideoid(int videoid)
{
    video_id = videoid;
}

int CVideo::getUserid() const
{
    return user_id;
}

void CVideo::setUserid(int userid)
{
    user_id = userid;
}

string CVideo::getVideoname() const
{
    return video_name;
}

void CVideo::setVideoname(string videoname)
{
    video_name = videoname;
}

string CVideo::getVideopath() const
{
    return video_path;
}

void CVideo::setVideopath(string videopath)
{
    video_path = videopath;
}

string CVideo::getCoverpath() const
{
    return cover_path;
}

void CVideo::setCoverpath(string coverpath)
{
    cover_path = coverpath;
}

string CVideo::getVideotime() const
{
    return video_time;
}

void CVideo::setVideotime(string videotime)
{
    video_time = videotime;
}

int CVideo::getVideocurrent() const
{
    return video_current;
}

void CVideo::setVideocurrent(int videocurrent)
{
    video_current = videocurrent;
}

int CVideo::getVideoalltime() const
{
    return video_alltime;
}

void CVideo::setVideoalltime(int videoalltime)
{
    video_alltime = videoalltime;
}

string CVideo::getLastplaytime() const
{
    return last_play_time;
}

void CVideo::setLastplaytime(string lastplaytime)
{
    last_play_time = lastplaytime;
}

