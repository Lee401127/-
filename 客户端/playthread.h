#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H
#include<QMutex>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <QThread>
#include <QWidget>
using namespace std;
using namespace cv;

class PlayThread:public QThread
{
    Q_OBJECT
public:
    PlayThread(string videopath);
    ~PlayThread();
    QImage MatToQImage(Mat& mat);
    void setPlayStatus(bool status);
    void setStartStatus(bool status);
    void setRestartStatus(bool status);
    void setNowFrame(int frame);
    void setThreadStopStatus(bool status);
    bool getPlayStatus();
    bool getStartStatus();
    void setSpeed(double speed);  // 新增设置速度方法

    bool getRestartStatus();
    QImage displayFirstFrame();
private:
    string videopath;
    volatile bool playstatus;
    volatile bool startstatus;
    volatile bool needrestart;
    volatile bool jumpframeStatus;
    volatile bool threadStop;
   // double speedMultiplier = 1.0; // 速度倍数（默认1x）
      //double fps = 30.0;            // 视频帧率
    int nowFrame;
    double m_speedMultiplier;  // 速度倍数（默认1x）
       double m_fps;              // 视频帧率
       QMutex m_speedMutex;       // 保护速度变量的锁

protected:
    void run();
signals:
    void sendIMG(QImage,int);
};

#endif // PLAYTHREAD_H
