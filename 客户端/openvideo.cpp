#include "openvideo.h"
#include "ui_openvideo.h"
#include <QDebug>
OpenVideo::OpenVideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenVideo)
{
    this->setwin = new Setting;
    this->login = nullptr;
    ui->setupUi(this);
    QDir appDir(QCoreApplication::applicationDirPath());
    QString configDirPath = appDir.filePath("settingfile");
    configPath = QDir(configDirPath).filePath("parking_system.conf");
    setupVideo();
    init_connect();
}

OpenVideo::~OpenVideo()
{
    delete ui;
}

void OpenVideo::setupVideo()
{
    video1.open("resourse/begin.mp4", cv::CAP_FFMPEG);
          if (!video1.isOpened()) {
              qDebug() << "无法打开视频文件！27";
              return;
          }

          timer = new QTimer(this);
          // 只保留一个timeout连接
          connect(timer, &QTimer::timeout, this, &OpenVideo::updateFrame);
          timer->start(40);
}

void OpenVideo::init_connect()
{
    connect(this,SIGNAL(over()),this,SLOT(change()));
    connect(this->setwin,SIGNAL(finish()),this,SLOT(turn()));
}

void OpenVideo::showFrame(QLabel *label, Mat frame)
{
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
       QImage img(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
       ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(), Qt::KeepAspectRatio));
}

void OpenVideo::change()
{

    if (!QFileInfo::exists(configPath)) {




      this->hide();
      this->setwin->show();
        qDebug() << "配置文件不存在";
    } else {
      this->hide();
      showLoginWidget();

    }
}

void OpenVideo::updateFrame()
{
    cv::Mat frame;
       if (video1.read(frame)) {

           showFrame(this->ui->label, frame);
       } else {

           timer->stop();
           video1.release();
           emit over();
       }
}

void OpenVideo::turn()
{
    this->setwin->hide();
    showLoginWidget();
}

void OpenVideo::showLoginWidget()
{
    if (this->login == nullptr) {
        this->login = new LoginWidget;
    }
    this->login->show();
}
