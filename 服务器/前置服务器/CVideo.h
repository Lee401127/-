#pragma once
#include<string>
#include<iostream>
using namespace std;
class CVideo
{
private:
    int video_id;	//视频id
    int user_id;	//用户id
    string video_name;	//视频名称
    string video_path;	//视频路径
    string cover_path;	//封面路径
    string video_time;	//视频记录上次保存时间
    int video_current;	//上次播放进度
    int video_alltime;	//视频总时长
    string last_play_time;	//上次播放时间
public:
    int getVideoid() const;
    void setVideoid(int videoid);

    int getUserid() const;
    void setUserid(int userid);

    string getVideoname() const;
    void setVideoname(string videoname);

    string getVideopath() const;
    void setVideopath(string videopath);

    string getCoverpath() const;
    void setCoverpath(string coverpath);

    string getVideotime() const;
    void setVideotime(string videotime);

    int getVideocurrent() const;
    void setVideocurrent(int videocurrent);

    int getVideoalltime() const;
    void setVideoalltime(int videoalltime);

    string getLastplaytime() const;
    void setLastplaytime(string lastplaytime);

};

