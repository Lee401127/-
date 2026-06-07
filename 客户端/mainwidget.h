#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include<QTimer>
#include<QLabel>
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include<QMessageBox>
#include"encryptiondecryption.h"
#include <opencv2/opencv.hpp>
#include"videoplayer.h"
#include <QMetaType> // 添加头文件
#include <QLineEdit>
#include"socketmode.h"
#include<QTableWidgetItem>
#include <QPixmap>
#include <QDateTime>
#include <QDir>
#include<QGridLayout>
#include<QList>
#include<QTreeWidgetItem>
#include <QCameraInfo>
#include <QListWidget>
#include <QVariant>
#include<QListWidgetItem>
#include <QDialog>
#include"videoplayer.h"
namespace Ui {
class Mainwidget;
}

class Mainwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Mainwidget(QWidget *parent = nullptr);
    ~Mainwidget();
    void updateTime();
     void setupVideo();
     void setuserid(QString userid);
    void refreshCameraList();
        void clearParentChildren();
        void listwidget();
private slots:
    void on_pushButton_5_clicked();
    bool eventFilter(QObject *obj, QEvent *event);
    void on_pushButton_4_clicked();
    void showSingleLabel(QLabel* target);
    void on_pushButton_3_clicked();
    void showAllLabels();
    void on_pushButton_11_clicked();

    void on_pushButton_21_clicked();
void processFallDetection(cv::Mat &frame);
    void on_pushButton_22_clicked();
void init_data(Video *video);
void init_data2(Picture *picture);
    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_26_clicked();
    void updateFrame();
    void showFrame(QLabel* label, cv::Mat frame);
    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();
    void onItemExpanded(QTreeWidgetItem *item);
    void onItemCollapsed(QTreeWidgetItem *item);
    void addlist();
    void addtimelist();
    void addlist1();
    void addtimelist1();
    void startRecording();   // 开始一次10秒录制
    void stopRecording();    // 停止当前录制（10秒后自动调用）
 void init_connect();
    void onNewFrame(const cv::Mat &frame);
  void getlistwarn();
    void init_timedata(const QList<QString> dateList);
    void init_timedata1(const QList<QString> dateList);
    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_treeWidget_2_itemClicked(QTreeWidgetItem *item, int column);
    void sendfilesuccess();
    void sendfilewarn();

    void sendvideosuccess(QString file);
    void sendvideowarn();

    void on_listWidget_2_itemClicked(QListWidgetItem *item);


    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_pushButton_9_clicked();

signals:
    void logoutRequested();

private:
    void stopRealtimeWork();
    void clearPictureData();
    void clearPictureTree();
    void showPicturePreview(const QString &imagePath, const QString &title);
    QString userid;
    Ui::Mainwidget *ui;
    QString formattedTime;//系统时间
    cv::VideoCapture video1;
    cv::VideoCapture video2;
    cv::VideoCapture video3;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
    bool isSingleChannel;
    QTreeWidgetItem *parentItem;
    QTreeWidgetItem *parentItem1;
    QList<settingfile> readConfigfile(const string &path);
    QGridLayout *videoLayout; // 必须手动记录布局指针
    QList<QLabel*> videoLabels; // 方便批量操作
    cv::Ptr<cv::BackgroundSubtractorMOG2> m_bgSubtractor; // 背景扣除器

    QList<Video*>videolist;
    QString savePath;
    QList<QString>dateList;
    QList<QTreeWidgetItem*>dateItems;
    QList<QListWidgetItem*>videoItems;
    QTreeWidgetItem *dateItem;
    QListWidgetItem *videoItem;

    QList<Picture*>picturelist;
    QList<QString>dateList1;
    QList<QTreeWidgetItem*>dateItems1;
    QList<QListWidgetItem*>pictureItems;
    QTreeWidgetItem *dateItem1;
    QListWidgetItem *pictureItem;



       cv::VideoWriter m_videoWriter; // 当前视频写入器
       cv::Mat m_savedFrame1;         // 最新帧（用于封面）
       bool m_isRecording;            // 是否正在录制
       int m_frameWidth, m_frameHeight;
       double m_fps;
       int m_recordedFrames;          // 当前已录帧数（可选）
       QString m_currentVideoPath;    // 当前视频文件路径
    EncryptionDecryption crcValidator;
       QMutex m_recordMutex;          // 保护 m_isRecording, m_videoWriter
       QMutex m_frameMutex;           // 保护 m_savedFrame1
       bool m_hasPerson ;
       int fallCounter;
       bool fallAlerted;
       double m_learningRate ; // 默认
VideoPlayer *c;
};

#endif // MAINWIDGET_H

