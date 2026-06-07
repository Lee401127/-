#include "playthread.h"

PlayThread::PlayThread(string videopath)
{
    this->videopath=videopath;
    this->playstatus=false;
    this->startstatus=false;
    this->needrestart=false;
    this->jumpframeStatus=false;
    this->nowFrame = 0;
    this->threadStop=false;
    this->m_speedMultiplier = 1.0;  // 默认速度1x

       // 新增：获取视频的实际帧率
       VideoCapture tempCap(videopath);
       m_fps = tempCap.get(CAP_PROP_FPS);
       if (m_fps <= 0.0) {
                 m_fps = 30.0; // 兜底帧率，避免后续除零
             }
             tempCap.release();
}

PlayThread::~PlayThread()
{
    this->setThreadStopStatus(true);
    wait();
}

QImage PlayThread::MatToQImage(Mat &mat)
{
    if (mat.channels() == 1)
    {
        // 单通道图像（灰度图）
        QImage qimg(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
        return qimg.copy();
    } else if (mat.channels() == 3)
    {
        // 三通道图像（BGR格式）
        Mat rgbMat;
        cvtColor(mat, rgbMat, COLOR_BGR2RGB);
        QImage qimg(rgbMat.data, rgbMat.cols, rgbMat.rows, rgbMat.step, QImage::Format_RGB888);
        return qimg.copy();
    }
    return QImage();
}

void PlayThread::setPlayStatus(bool status)
{
    this->playstatus=status;
}

void PlayThread::setStartStatus(bool status)
{
    this->startstatus=status;
}

void PlayThread::setRestartStatus(bool status)
{
    this->needrestart=status;
}

void PlayThread::setNowFrame(int frame)
{
    this->jumpframeStatus=true;
    this->playstatus=true;
    this->nowFrame=frame;
}

void PlayThread::setThreadStopStatus(bool status)
{
    this->threadStop=status;
}

bool PlayThread::getPlayStatus()
{
    return this->playstatus;
}

bool PlayThread::getStartStatus()
{
    return this->startstatus;
}

void PlayThread::setSpeed(double speed)
{
    if (speed > 0) {
           m_speedMultiplier = speed;
       }
}

bool PlayThread::getRestartStatus()
{
    return this->needrestart;
}

QImage PlayThread::displayFirstFrame()
{
    Mat frame;
    VideoCapture video(this->videopath);
    if (video.read(frame)) {
        QImage img = MatToQImage(frame);
        QPixmap pixmap = QPixmap::fromImage(img);
        video.release();
        return img;
    }
    video.release();
    return QImage();
}

void PlayThread::run()
{
    Mat frame;
    VideoCapture video(this->videopath);
    while(!this->threadStop)
    {
        if(this->needrestart)
        {
            video.set(cv::CAP_PROP_POS_FRAMES, 0); // 将视频定位到第一帧
            this->nowFrame=0;
            this->needrestart = false;
        }
        if(this->jumpframeStatus)
        {
            video.set(cv::CAP_PROP_POS_FRAMES, this->nowFrame);
            this->jumpframeStatus=false;
        }
        while(!playstatus)
        {
            if(playstatus)
            {
                break;
            }
        }
        if(!video.read(frame))
        {
            break;
        }
        QImage img=this->MatToQImage(frame);
        emit sendIMG(img,this->nowFrame);
        this->nowFrame++;
        // 修改帧延迟计算逻辑
              QMutexLocker locker(&m_speedMutex);
              const double effectiveFps = (m_fps > 0.0) ? m_fps : 30.0;
                     int delay = static_cast<int>(1000 / (effectiveFps * m_speedMultiplier));
              msleep(delay > 0 ? delay : 40);  // 最低延迟40ms保护
          }
          this->threadStop = false;

}
