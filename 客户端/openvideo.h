#ifndef OPENVIDEO_H
#define OPENVIDEO_H

#include <QWidget>
#include<QTimer>
//#include "ui_animationview.h"
#include<opencv2/opencv.hpp>

#include<QMessageBox>
#include"loginwidget.h"
#include"setting.h"
using namespace std;
using namespace cv;
namespace Ui {
class OpenVideo;
}

class OpenVideo : public QWidget
{
    Q_OBJECT

public:
    explicit OpenVideo(QWidget *parent = nullptr);
    ~OpenVideo();
    void setupVideo();
    void init_connect();
    void showFrame(QLabel* label, cv::Mat frame);
private slots:
      void change();
      void updateFrame() ;
      void turn();
private:
    Ui::OpenVideo *ui;
    QTimer *timer;
  VideoCapture video1;
       VideoCapture capture;
       Mat frame;
       Setting *setwin;
       LoginWidget *login;
        QString configPath ;
    void showLoginWidget();
signals:
       void over();
};

#endif // OPENVIDEO_H
