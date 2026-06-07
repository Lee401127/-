#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScreen>

Mainwidget::Mainwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwidget)
{
    timer1 = nullptr;
    timer2 = nullptr;
    timer3 = nullptr;
    ui->setupUi(this);
    QTimer* timeUpdateTimer = new QTimer(this);
   // setupVideo();
    refreshCameraList();
    // 显式连接，避免依赖 Qt 自动槽命名导致 itemClicked 不触发
    connect(ui->listWidget, &QListWidget::itemClicked,
            this, &Mainwidget::on_listWidget_itemClicked);
    connect(ui->listWidget, &QListWidget::itemDoubleClicked,
            this, &Mainwidget::on_listWidget_itemClicked);

    // 1. 初始化 Label 列表
        videoLabels = {ui->label, ui->label_2, ui->label_3, ui->label_4};


          // 为每个label安装事件过滤器
          for (QLabel* label : videoLabels) {
              label->installEventFilter(this);
          }
        // 2. 为 ui->page (StackedWidget第一页) 设置网格布局
        // 注意：如果 UI 设计师里 page 已经有布局，先删除或直接获取
        videoLayout = new QGridLayout(ui->widget);
        videoLayout->setSpacing(2);
        videoLayout->setContentsMargins(0, 0, 0, 0);
        isSingleChannel=true;
        m_bgSubtractor = cv::createBackgroundSubtractorMOG2(500, 16, true);
        // 3. 将你的 Label 按照 2x2 放入布局
        videoLayout->addWidget(ui->label, 0, 0);
        videoLayout->addWidget(ui->label_2, 0, 1);
        videoLayout->addWidget(ui->label_3, 1, 0);
        videoLayout->addWidget(ui->label_4, 1, 1);

        m_frameWidth = 0;
          m_isRecording=false,
        m_frameHeight = 0;
          m_bgSubtractor = cv::createBackgroundSubtractorMOG2(500, 16, true); // 开启阴影检测
           m_hasPerson = false;
           m_learningRate = 0.01; // 默认
              m_fps=30.0;
              m_recordedFrames=0;
              int fallCounter = 0;
              bool fallAlerted = false;
    QTimer::singleShot(1000, this, &Mainwidget::startRecording);
    listwidget();
    init_connect();
    this->parentItem = new QTreeWidgetItem(this->ui->treeWidget_2);
    parentItem->setText(0, QString::fromLocal8Bit("监控回放目录"));
    parentItem->setCheckState(2, Qt::Unchecked);  // 在列 2 设置复选框
    parentItem->setIcon(0, QIcon(":/resource/收藏夹.png"));  // 第一个参数为列索引

    this->parentItem1 = new QTreeWidgetItem(this->ui->treeWidget);
    parentItem1->setText(0, QString::fromLocal8Bit("监控回放目录"));
    parentItem1->setCheckState(2, Qt::Unchecked);  // 在列 2 设置复选框
    parentItem1->setIcon(0, QIcon(":/resource/收藏夹.png"));  // 第一个参数为列索引
    connect(timeUpdateTimer, &QTimer::timeout, this, &Mainwidget::updateTime);
    connect(this->ui->treeWidget_2, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(onItemExpanded(QTreeWidgetItem*)));
    connect(this->ui->treeWidget_2, SIGNAL(itemCollapsed(QTreeWidgetItem*)), this, SLOT(onItemCollapsed(QTreeWidgetItem*)));
    connect(this->ui->treeWidget, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(onItemExpanded(QTreeWidgetItem*)));
    connect(this->ui->treeWidget, SIGNAL(itemCollapsed(QTreeWidgetItem*)), this, SLOT(onItemCollapsed(QTreeWidgetItem*)));
    timeUpdateTimer->start(1000);
}

Mainwidget::~Mainwidget()
{
    stopRealtimeWork();
    delete ui;
}
void Mainwidget::updateTime()
{

        QDateTime currentTime = QDateTime::currentDateTime();
        formattedTime = currentTime.toString("yyyy-MM-dd HH:mm:ss");
        this->ui->systemtime_label->setText("当前系统时间："+formattedTime);

}

void Mainwidget::setupVideo()
{
    // 重新进入页面时，先清理旧的实时任务，避免重复定时器继续跑
    stopRealtimeWork();

    video1.open("resourse/2.mp4");
      //video1.open(0);
      if (!video1.isOpened()) {
          qDebug() << "无法打开视频文件1！";
          return;
      }

      timer1 = new QTimer(this);
      connect(timer1, &QTimer::timeout, this, &Mainwidget::updateFrame);
      timer1->start(40);  // 25fps
}

void Mainwidget::stopRealtimeWork()
{
    if (timer1) {
        timer1->stop();
        timer1->deleteLater();
        timer1 = nullptr;
    }
    if (timer2) {
        timer2->stop();
        timer2->deleteLater();
        timer2 = nullptr;
    }
    if (timer3) {
        timer3->stop();
        timer3->deleteLater();
        timer3 = nullptr;
    }

    if (video1.isOpened()) video1.release();
    if (video2.isOpened()) video2.release();
    if (video3.isOpened()) video3.release();

    {
        QMutexLocker locker(&m_recordMutex);
        if (m_videoWriter.isOpened()) {
            m_videoWriter.release();
        }
        m_isRecording = false;
    }
}

void Mainwidget::on_pushButton_5_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
    for (auto p : this->picturelist) {
        delete p;
    }
    this->picturelist.clear();
    this->ui->listWidget->clear();
    char sendbuf[8192];
    GET_PICTURE_REQ get_picture_req;
    get_picture_req.from=0;
    get_picture_req.to=MAX_PICTURE - 1;
    get_picture_req.type=0; // 0 按月
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    strcpy(get_picture_req.time,timestamp.toUtf8());

    HEAD head;
    head.data_len=sizeof(GET_PICTURE_REQ );
    head.service_type=GET_PICTURE_LIST;



    // 封装数据

    memcpy(sendbuf,&head,sizeof(HEAD));
    memcpy(sendbuf+sizeof(HEAD),&get_picture_req,head.data_len);
    crcValidator.GenerateChecksum(sendbuf,sizeof(HEAD)+sizeof(GET_PICTURE_REQ));
    Socketmode::getInstance()->sendmsg(sendbuf,sizeof(HEAD)+sizeof(GET_PICTURE_REQ));
    qDebug()<<"126"<<endl;
}

bool Mainwidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
            QLabel *clickedLabel = qobject_cast<QLabel*>(obj);
            if (clickedLabel) {
                if (!isSingleChannel) {
                    showSingleLabel(clickedLabel);

                } else {
                    showAllLabels();
                }
                return true;
            }
        }
        return QWidget::eventFilter(obj, event);
}

void Mainwidget::on_pushButton_4_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(2);
    this->videolist.clear(); // 发起新请求前清空旧数据
    this->ui->listWidget_2->clear();
    char sendbuf[8192];
    GET_VIDEO_REQ get_video_req;
    get_video_req.from=0;
    get_video_req.to=14;
    get_video_req.type=0;
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    strcpy(get_video_req.time,timestamp.toUtf8());

    HEAD head;
    head.data_len=sizeof(GET_VIDEO_REQ );
    head.service_type=GET_VIDEO_LIST;



    // 封装数据

    memcpy(sendbuf,&head,sizeof(HEAD));
    memcpy(sendbuf+sizeof(HEAD),&get_video_req,head.data_len);
    crcValidator.GenerateChecksum(sendbuf,sizeof(HEAD)+sizeof(GET_VIDEO_REQ));
    Socketmode::getInstance()->sendmsg(sendbuf,sizeof(HEAD)+sizeof(GET_VIDEO_REQ));
    qDebug()<<"126"<<endl;
}

void Mainwidget::showSingleLabel(QLabel *target)
{
    for (QLabel* label : videoLabels) {
            if (label == target) {
                label->show();
                // 选中的 Label 会因为其他 Label 的隐藏而自动占据整个布局空间
            } else {
                label->hide();
            }
        }
        isSingleChannel = true;
}


void Mainwidget::on_pushButton_3_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(3);
}

void Mainwidget::showAllLabels()
{
    for (QLabel* label : videoLabels) {
            label->show();
        }
        isSingleChannel = false;
}

void Mainwidget::on_pushButton_11_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void Mainwidget::on_pushButton_21_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(2);
    this->videolist.clear(); // 发起新请求前清空旧数据
    this->ui->listWidget_2->clear();
    char sendbuf[8192];
    GET_VIDEO_REQ get_video_req;
    get_video_req.from=0;
    get_video_req.to=5;
    get_video_req.type=0;
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    strcpy(get_video_req.time,timestamp.toUtf8());

    HEAD head;
    head.data_len=sizeof(GET_VIDEO_REQ );
    head.service_type=GET_VIDEO_LIST;


    // 封装数据

    memcpy(sendbuf,&head,sizeof(HEAD));
    memcpy(sendbuf+sizeof(HEAD),&get_video_req,head.data_len);
    crcValidator.GenerateChecksum(sendbuf,sizeof(HEAD)+sizeof(GET_VIDEO_REQ));
    Socketmode::getInstance()->sendmsg(sendbuf,sizeof(HEAD)+sizeof(GET_VIDEO_REQ));
}

void Mainwidget::processFallDetection(Mat &frame)
{
    cv::Mat gray, blur, thresh;

        // 1. 预处理：转灰度并平滑噪点
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(gray, blur, cv::Size(5, 5), 0);

        // 2. 二值化：提取前景（此处假设背景较暗，实际环境建议使用背景减除法 BackgroundSubtractor）
        cv::threshold(blur, thresh, 50, 255, cv::THRESH_BINARY);

        // 3. 寻找轮廓
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (size_t i = 0; i < contours.size(); i++) {
            double area = cv::contourArea(contours[i]);
            if (area < 3000) continue; // 过滤掉太小的干扰物

            // 4. 获取人体外接矩形
            cv::Rect rect = cv::boundingRect(contours[i]);

            // 5. 计算纵横比 (宽 / 高)
            double ratio = (double)rect.width / rect.height;

            // 6. 判定逻辑
            if (ratio > 1.1) { // 阈值可调，通常跌倒后宽度会大于高度
                // 绘制红框表示警告
                cv::rectangle(frame, rect, cv::Scalar(0, 0, 255), 3);
                cv::putText(frame, "FALL DETECTED!", cv::Point(rect.x, rect.y - 10),
                            cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 0, 255), 2);

                // 这里可以触发报警信号，例如 QMessageBox 或蜂鸣器
                qDebug() << "Warning: Person Fall Detected!";
            } else {
                // 正常状态绘制绿框
                cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
            }
        }
}

void Mainwidget::on_pushButton_22_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(3);
}

void Mainwidget::init_data(Video *video)
{
   /* this->videolist.clear();
    this->videolist.append(video);
    addlist();*/
    Video* newVideo = new Video;
        memcpy(newVideo, video, sizeof(Video));
        this->videolist.append(newVideo);

        // 收到数据后直接更新显示
        addlist();

}

void Mainwidget::init_data2(Picture *picture)
{
    if (!picture) return;
    // 只保留类型=3（抓拍）
    if (picture->picture_type != 3) {
        delete picture;
        return;
    }

    Picture *newPicture = new Picture;
    memcpy(newPicture, picture, sizeof(Picture));
    this->picturelist.append(newPicture);

    // 收到数据后直接更新显示
    addlist1();
    delete picture;
}

void Mainwidget::on_pushButton_24_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void Mainwidget::on_pushButton_25_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
    for (auto p : this->picturelist) {
        delete p;
    }
    this->picturelist.clear();
    this->ui->listWidget->clear();
    char sendbuf[8192];
    GET_PICTURE_REQ get_picture_req;
    get_picture_req.from=0;
    get_picture_req.to=MAX_PICTURE - 1;
    get_picture_req.type=0; // 0 按月
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    strcpy(get_picture_req.time,timestamp.toUtf8());

    HEAD head;
    head.data_len=sizeof(GET_PICTURE_REQ );
    head.service_type=GET_PICTURE_LIST;



    // 封装数据

    memcpy(sendbuf,&head,sizeof(HEAD));
    memcpy(sendbuf+sizeof(HEAD),&get_picture_req,head.data_len);
    crcValidator.GenerateChecksum(sendbuf,sizeof(HEAD)+sizeof(GET_PICTURE_REQ));
    Socketmode::getInstance()->sendmsg(sendbuf,sizeof(HEAD)+sizeof(GET_PICTURE_REQ));
    qDebug()<<"126"<<endl;
}

void Mainwidget::on_pushButton_23_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(3);
}

void Mainwidget::on_pushButton_26_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void Mainwidget::updateFrame()
{
    cv::Mat frame;
         if (video1.read(frame)) {
             if (frame.empty()) return;

             // 1. 备份当前帧供保存封面使用
             {
                 QMutexLocker locker(&m_frameMutex);
                 frame.copyTo(m_savedFrame1);
             }

             // 2. 录制逻辑（原 onNewFrame 迁移至此）
             if (m_isRecording) {
                 QMutexLocker locker(&m_recordMutex);
                 if (m_videoWriter.isOpened()) {
                     m_videoWriter.write(frame);
                     m_recordedFrames++;
                 }
             }

             // 跌倒检测部分
             cv::Mat fgMask, fgBinary;
             m_bgSubtractor->apply(frame, fgMask, m_learningRate);

             // 形态学去噪 + 阴影过滤
             cv::morphologyEx(fgMask, fgMask, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3,3)));
             cv::threshold(fgMask, fgBinary, 200, 255, cv::THRESH_BINARY);
             cv::morphologyEx(fgBinary, fgBinary, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));

             std::vector<std::vector<cv::Point>> contours;
             cv::findContours(fgBinary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

             bool hasPerson = false;
             for (const auto& contour : contours) {
                 double area = cv::contourArea(contour);
                 if (area < 2000) continue;
                 hasPerson = true;

                 cv::Rect rect = cv::boundingRect(contour);
                 rect &= cv::Rect(0, 0, frame.cols, frame.rows); // 确保边界

                 double ratio = (double)rect.width / rect.height;
                 double fillRatio = area / rect.area();

                 // 跌倒判断条件
                 if (ratio > 1.3 && fillRatio > 0.3 && fillRatio < 0.8 && area > 3000) {
                     // 连续帧计数
                     fallCounter++;
                     if (fallCounter > 5 && !fallAlerted) {
                         cv::rectangle(frame, rect, cv::Scalar(0, 0, 255), 3);
                         cv::putText(frame, "FALL DETECTED!", rect.tl(), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 0, 255), 2);
                         qDebug() << "Fall detected!";
                         // ========== 新增：保存摔倒瞬间帧并发送 ==========
                            // 生成唯一文件名（时间戳）
                            QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

                            // 读取配置获取保存路径（建议将 configs 缓存，避免每次读取文件）
                            QList<settingfile> configs = readConfigfile("./settingfile/parking_system.conf");
                            if (configs.isEmpty()) {
                                qDebug() << "配置文件读取失败：./settingfile/parking_system.conf 为空，跳过抓拍保存";
                                fallAlerted = true;
                                break;
                            }

                            QString savePath = QString::fromUtf8(configs.first().image_path.c_str());
                            if (savePath.isEmpty()) {
                                qDebug() << "image_save_path 为空，跳过抓拍保存";
                                fallAlerted = true;
                                break;
                            }

                            QDir saveDir(savePath);
                            if (!saveDir.exists() && !saveDir.mkpath(".")) {
                                qDebug() << "图片保存目录创建失败：" << savePath;
                                fallAlerted = true;
                                break;
                            }

                            // 文件名里不要包含 ':' 等特殊字符（不同平台可能非法）
                            QString filename = QString("%1.jpg").arg(timestamp).replace(':', '-');
                            QString fullPath = saveDir.filePath(filename);
                            QString fileOnly = QFileInfo(fullPath).fileName();

                            // 保存当前帧（frame 是已经绘制了红框的 Mat，即摔倒瞬间图像）
                            if (cv::imwrite(fullPath.toStdString(), frame)) {
                                qDebug() << "摔倒抓拍已保存：" << fullPath;

                                // 构建 Picture 结构体并发送到服务器
                                Picture picture;
                                strncpy(picture.picture_name, fileOnly.toUtf8().constData(), sizeof(picture.picture_name) - 1);
                                picture.picture_name[sizeof(picture.picture_name) - 1] = '\0';
                                strncpy(picture.picture_time, timestamp.toUtf8().constData(), sizeof(picture.picture_time) - 1);
                                picture.picture_time[sizeof(picture.picture_time) - 1] = '\0';
                                picture.picture_type = 3;  // 摔倒报警类型

                                char sendbuf[sizeof(HEAD) + sizeof(PICTURE_REQ)] = {0};
                                PICTURE_REQ picture_req = {0};
                                strncpy(picture_req.phone, this->userid.toUtf8().constData(), sizeof(picture_req.phone) - 1);
                                picture_req.phone[sizeof(picture_req.phone) - 1] = '\0';
                                picture_req.picture = picture;

                                HEAD head;
                                head.data_len = sizeof(PICTURE_REQ);
                                head.service_type = SEND_PICTURE;  // 确保服务端有对应的处理类型

                                memcpy(sendbuf, &head, sizeof(HEAD));
                                memcpy(sendbuf + sizeof(HEAD), &picture_req, head.data_len);

                                // 计算校验和并发送
                                crcValidator.GenerateChecksum(sendbuf, sizeof(HEAD) + sizeof(PICTURE_REQ));
                                Socketmode::getInstance()->sendmsg(sendbuf, sizeof(HEAD) + sizeof(PICTURE_REQ));
                            } else {
                                qDebug() << "错误：摔倒抓拍保存失败！";
                            }
                         fallAlerted = true;
                     }
                 } else {
                     // 正常画绿框（仅显示较大目标）
                     if (area > 3000) {
                         cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
                     }
                 }
             }

             // 动态学习率
             m_learningRate = hasPerson ? 0.001 : 0.01;
             // 若连续多帧无人，可重置背景（可选）
             if (!hasPerson) {
                 fallCounter = 0;
                 fallAlerted = false;
             }

             // 4. 显示画面
             showFrame(ui->label, frame);

                      showFrame(ui->label_2, frame);

                      showFrame(ui->label_3, frame);

                      showFrame(ui->label_4, frame);
         } else {
             // 循环播放
             video1.set(cv::CAP_PROP_POS_FRAMES, 0);
         }
}

void Mainwidget::showFrame(QLabel *label, Mat frame)
{   if(frame.empty()) return;



    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

    QImage img(

        frame.data,

        frame.cols,

        frame.rows,

        frame.step,

        QImage::Format_RGB888

    );



    label->setPixmap(QPixmap::fromImage(img)

        .scaled(label->size(),

                Qt::KeepAspectRatioByExpanding,

                Qt::SmoothTransformation));

}

void Mainwidget::on_pushButton_7_clicked()
{
showSingleLabel(ui->label);;
}

void Mainwidget::on_pushButton_8_clicked()
{
    showAllLabels();
}

void Mainwidget::on_pushButton_9_clicked()
{
    stopRealtimeWork();
    this->userid.clear();
    this->hide();
    emit logoutRequested();
}

void Mainwidget::onItemExpanded(QTreeWidgetItem *item)
{
    qDebug() << "Item Expanded:" << item->text(0);
}

void Mainwidget::onItemCollapsed(QTreeWidgetItem *item)
{
    qDebug() << "Item Collapsed:" << item->text(0);
}

void Mainwidget::addlist()
{
    this->ui->listWidget_2->clear();
    this->videoItems.clear();
    for (int j=0;j<this->videolist.size();j++) {
        QList<settingfile> configs  = readConfigfile("./settingfile/parking_system.conf");
        if (configs.isEmpty()) {
            qDebug() << "配置文件读取失败：./settingfile/parking_system.conf 为空，跳过视频封面加载";
            return;
        }
        savePath= QString::fromUtf8(configs.first().video_path.c_str());
        qDebug() << "Cover path:" << savePath+"/"+this->videolist.at(j)->cover_path;



            this->videoItem=new QListWidgetItem(QIcon(savePath+"/"+this->videolist.at(j)->cover_path),this->videolist.at(j)->video_name);
            QString picturePath = this->videolist.at(j)->video_name;

            videoItems.append(videoItem);
            this->ui->listWidget_2->addItem(this->videoItem);

    }
}

void Mainwidget::addtimelist()
{
    // 清空树控件和缓存列表
    //    this->ui->treeWidget->clear();
        this->dateItems.clear();
        clearParentChildren();
        // 创建或复用父节点
        if (!this->parentItem) {
            this->parentItem = new QTreeWidgetItem(this->ui->treeWidget_2);
            this->parentItem->setText(0, "日期列表");
        }

        // 检查 datelist 是否为空
        if (this->dateList.isEmpty()) {
            // 插入默认提示项
            QTreeWidgetItem *defaultItem = new QTreeWidgetItem(this->parentItem);
            defaultItem->setText(0, "暂无可用日期");
            defaultItem->setFlags(Qt::NoItemFlags);  // 设置为不可交互
            this->dateItems.append(defaultItem);
        } else {
            // 正常插入日期项
            for (int j = 0; j < this->dateList.size(); j++) {
                QTreeWidgetItem *dateItem = new QTreeWidgetItem(this->parentItem);
                dateItem->setText(0, this->dateList.at(j));
                this->dateItems.append(dateItem);
            }
        }

        // 展开父节点以显示子项
        this->parentItem->setExpanded(true);
}

void Mainwidget::addlist1()
{
    this->ui->listWidget->clear();
    this->pictureItems.clear();
    for (int j=0;j<this->picturelist.size();j++) {
        QList<settingfile> configs  = readConfigfile("./settingfile/parking_system.conf");
        if (configs.isEmpty()) {
            qDebug() << "配置文件读取失败：./settingfile/parking_system.conf 为空，跳过图片加载";
            return;
        }
        savePath= QString::fromUtf8(configs.first().image_path.c_str());
        qDebug() << " path:" << savePath+"/"+this->picturelist.at(j)->picture_name;
qDebug() << " time:" << savePath+"/"+this->picturelist.at(j)->picture_time;

            QString fullPicturePath = savePath+"/"+this->picturelist.at(j)->picture_name;
            this->pictureItem=new QListWidgetItem(QIcon(fullPicturePath),this->picturelist.at(j)->picture_name);
            this->pictureItem->setData(Qt::UserRole, fullPicturePath);

            pictureItems.append(pictureItem);
            this->ui->listWidget->addItem(this->pictureItem);

    }
}

void Mainwidget::addtimelist1()
{
    // 清空树控件和缓存列表
    //    this->ui->treeWidget->clear();
        this->dateItems1.clear();
        clearPictureTree();
        // 创建或复用父节点
        if (!this->parentItem1) {
            this->parentItem1 = new QTreeWidgetItem(this->ui->treeWidget);
            this->parentItem1->setText(0, "日期列表");
        }

        // 检查 datelist 是否为空
        if (this->dateList1.isEmpty()) {
            // 插入默认提示项
            QTreeWidgetItem *defaultItem = new QTreeWidgetItem(this->parentItem1);
            defaultItem->setText(0, "暂无可用日期");
            defaultItem->setFlags(Qt::NoItemFlags);  // 设置为不可交互
            this->dateItems1.append(defaultItem);
        } else {
            // 正常插入日期项
            for (int j = 0; j < this->dateList1.size(); j++) {
                QTreeWidgetItem *dateItem1 = new QTreeWidgetItem(this->parentItem1);
                dateItem1->setText(0, this->dateList1.at(j));
                this->dateItems1.append(dateItem1);
            }
        }

        // 展开父节点以显示子项
        this->parentItem1->setExpanded(true);
}

void Mainwidget::startRecording()
{
  /*  QMutexLocker locker(&m_recordMutex);

       // 如果已在录制，本次请求忽略（正常情况下不会发生，因为stop后才会调用start）
       if (m_isRecording) {
           qDebug() << "警告：正在录制中，本次启动忽略";
           return;
       }

       // 1. 获取视频参数
       m_frameWidth = static_cast<int>(video1.get(cv::CAP_PROP_FRAME_WIDTH));
       m_frameHeight = static_cast<int>(video1.get(cv::CAP_PROP_FRAME_HEIGHT));
       m_fps = video1.get(cv::CAP_PROP_FPS);
       if (m_fps <= 0) m_fps = 30.0;

       // 2. 参数有效性检查
       if (m_frameWidth <= 0 || m_frameHeight <= 0) {
           qDebug() << "错误：无效视频尺寸，1秒后重试";
           QTimer::singleShot(1000, this, &Mainwidget::startRecording);
           return;
       }

       // 3. 读取配置文件，获取保存目录
       QList<settingfile> configs = readConfigfile("./settingfile/parking_system.conf");
       if (configs.isEmpty()) {
           qDebug() << "错误：配置文件读取失败，1秒后重试";
           QTimer::singleShot(1000, this, &Mainwidget::startRecording);
           return;
       }
       QString savePath = QString::fromUtf8(configs.first().video_path.c_str());
       QDir dir(savePath);
       if (!dir.exists() && !dir.mkpath(".")) {
           qDebug() <<"错误：无法创建保存目录，1秒后重试：" << savePath;
           QTimer::singleShot(1000, this, &Mainwidget::startRecording);
            return;
       }



       // 4. 生成当前段的时间戳及文件路径
       QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
       m_currentVideoPath = dir.filePath(QString("%1.avi").arg(timestamp));
       QString imagePath = dir.filePath(QString("%1.jpg").arg(timestamp));
       QString coverPath = timestamp + ".jpg";
       QString videopath = timestamp + ".avi";

       // 5. 初始化 VideoWriter
       m_videoWriter.open(m_currentVideoPath.toLocal8Bit().constData(),
                          cv::VideoWriter::fourcc('M','J','P','G'),
                          m_fps,
                          cv::Size(m_frameWidth, m_frameHeight));
       if (!m_videoWriter.isOpened()) {
           qDebug() << "错误：无法创建视频文件，1秒后重试：" << m_currentVideoPath;
           QTimer::singleShot(1000, this, &Mainwidget::startRecording);
           return;
       }

       // 6. 保存第一帧作为封面（若有）
       {
           QMutexLocker frameLocker(&m_frameMutex);
           if (!m_savedFrame1.empty()) {
               if (cv::imwrite(imagePath.toStdString(), m_savedFrame1)) {
                   qDebug() << "封面已保存：" << imagePath;
                   // 可选：上报图片信息
                   // sendPictureInfo(coverPath, timestamp);
               } else {
                   qDebug() << "警告：封面保存失败";
               }
           } else {
               qDebug() << "警告：无可用帧，跳过封面保存";
           }
       }

       // 7. 标记录制开始
       m_isRecording = true;
       m_recordedFrames = 0;
       qDebug() << "▶️ 开始10秒录制，文件：" << m_currentVideoPath;

       Video video;
       strcpy(video.cover_path,coverPath.toUtf8());
       strcpy(video.video_name,videopath.toUtf8());
       strcpy(video.video_time,timestamp.toUtf8());
       video.video_alltime=900;
       video.video_current=0;
       strcpy(video.video_starttime,timestamp.toUtf8());
       strcpy(video.video_time,timestamp.toUtf8());
     qDebug() << "1" << coverPath.toUtf8()<<"2"<<videopath.toUtf8()<<"3"<<timestamp.toUtf8();
       char sendbuf[8192];
       VIDEO_REQ video_req={0};
       strcpy(video_req.phone,this->userid.toUtf8());
       video_req.video=video;
       video_req.type=0;

       HEAD head;
       head.data_len=sizeof(VIDEO_REQ);
       head.service_type=SEND_VIDEO;



       // 封装数据

       memcpy(sendbuf,&head,sizeof(HEAD));
       memcpy(sendbuf+sizeof(HEAD),&video_req,head.data_len);
        crcValidator.GenerateChecksum(sendbuf,sizeof(HEAD)+sizeof(VIDEO_REQ));
       Socketmode::getInstance()->sendmsg(sendbuf,sizeof(HEAD)+sizeof(VIDEO_REQ));

       // 9. 设置10秒后自动停止
       QTimer::singleShot(30000, this, &Mainwidget::stopRecording);*/
}

void Mainwidget::stopRecording()
{
  /*  {
          QMutexLocker locker(&m_recordMutex);
          if (m_isRecording) {
              m_videoWriter.release();
              m_isRecording = false;
              m_recordedFrames = 0;
              qDebug() << "⏹️ 10秒录制结束，文件已保存：" << m_currentVideoPath;
          }
      }

      // ！！！关键：立即启动下一次录制（无间隔）！！！
    QTimer::singleShot(0, this, &Mainwidget::startRecording);*/
}

void Mainwidget::init_connect()
{

    connect(Socketmode::getInstance()->acceptthread,SIGNAL(sendfilesuccess()),this,SLOT(sendfilesuccess()));
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(sendfilewarn()),this,SLOT(sendfilewarn()));
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(sendvideosuccess(QString)),this,SLOT(sendvideosuccess(QString)));
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(sendvideowarn()),this,SLOT(sendvideowarn()));

    connect(Socketmode::getInstance()->acceptthread,SIGNAL(getvideolistsuccess(Video*)),this,SLOT(init_data(Video*)));
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(getvideolistwarn()),this,SLOT(getlistwarn()));
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(getDateTimeListSuccess(QList<QString>)),this,SLOT(init_timedata(QList<QString>)),Qt::QueuedConnection);

    connect(Socketmode::getInstance()->acceptthread,SIGNAL(getpicturelistsuccess(Picture*)),this,SLOT(init_data2(Picture*)));
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(getpicturelistwarn()),this,SLOT(getlistwarn()));
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(getpictureDateTimeListSuccess(QList<QString>)),this,SLOT(init_timedata1(QList<QString>)),Qt::QueuedConnection);
}

void Mainwidget::onNewFrame(const Mat &frame)
{
    // 1. 更新最新帧（用于封面）
       {
           QMutexLocker locker(&m_frameMutex);
           frame.copyTo(m_savedFrame1);
       }

       // 2. 如果正在录制，写入视频
       if (m_isRecording) {
           QMutexLocker locker(&m_recordMutex);
           if (m_videoWriter.isOpened()) {
               m_videoWriter.write(frame);
               m_recordedFrames++;
           }
       }
}

void Mainwidget::getlistwarn()
{
    QMessageBox::information(this,"获取视频列表信息失败","视频列表信息");
}

void Mainwidget::init_timedata(const QList<QString> dateList)
{
    this->dateList.clear();
    this->dateList.append(dateList);
    qDebug()<<"568"<<endl;
    addtimelist();
}

void Mainwidget::init_timedata1(const QList<QString> dateList)
{
    this->dateList1.clear();
    this->dateList1.append(dateList);
    qDebug()<<"568"<<endl;
    addtimelist1();
}



QList<settingfile> Mainwidget::readConfigfile(const string &path)
{
    QList<settingfile> configList;
        settingfile config; // 创建临时配置对象
        // 将 std::string 转为 QString
           QString qPath = QString::fromStdString(path);

           // 转换为绝对路径
           QFileInfo fileInfo(qPath);
           QString absolutePath = fileInfo.absoluteFilePath();

           std::ifstream file(path);
           if (!file.is_open()) {
               std::cerr << "无法打开配置文件: " << path << std::endl;
               qDebug() << "配置文件绝对路径:580 " << absolutePath; // 打印绝对路径
               return configList;
           }
         qDebug() << "配置文件绝对路径: 583" << absolutePath; // 打印绝对路径

        std::string line;
        while (std::getline(file, line)) {
            // 移除注释和空白字符
            size_t commentPos = line.find('#');
            if (commentPos != std::string::npos) line = line.substr(0, commentPos);
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            if (line.empty()) continue;

            // 解析键值对
            size_t delimiterPos = line.find('=');
            if (delimiterPos == std::string::npos) continue;

            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            // 填充配置对象
            if (key == "server_ip") {
                config.server_ip = value;
            } else if (key == "server_port") {
                try {
                    config.server_port = std::stoi(value);
                } catch (...) {
                    std::cerr << "无效端口号: " << value << std::endl;
                }
            } else if (key == "image_save_path") {
                config.image_path = value;
            } else if (key == "video_save_path") {
                config.video_path = value;
            } else if (key == "storage_size") {
                try {
                    config.storage_size = std::stoi(value);
                } catch (...) {
                    std::cerr << "无效存储容量: " << value << std::endl;
                }
            }
        }

        file.close();
        configList.append(config); // 将配置对象加入列表
        return configList;
}

void Mainwidget::setuserid(QString userid)
{
    this->userid=userid;
    this->ui->user_numlabel->setText("当前用户："+this->userid);
}

void Mainwidget::refreshCameraList()
{
    ui->listWidget_3->clear();

        // 获取可用摄像头列表
        // QCameraInfo::availableCameras() 返回 QList<QCameraInfo>
        QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

        if (cameras.isEmpty()) {
            ui->listWidget_3->addItem("未发现摄像头设备");
            return;
        }

        for (const QCameraInfo &cameraInfo : cameras) {
            // description(): 摄像头的描述名称（如 "USB 2.0 Camera"）
            // deviceName(): 系统内部设备名（在 Linux 下通常是 "/dev/video0"）
            QString displayName = cameraInfo.description();

            // 如果没有描述信息，则显示设备节点名
            if (displayName.isEmpty()) {
                displayName = cameraInfo.deviceName();
            }

            QListWidgetItem *item = new QListWidgetItem(displayName);

            // 关键点：将 cameraInfo 的设备名存入 UserRole，方便后面开启摄像头时调用
            item->setData(Qt::UserRole, cameraInfo.deviceName());

            ui->listWidget_3->addItem(item);
        }
}

void Mainwidget::clearParentChildren()
{
    if (this->parentItem) {
        // 循环移除并删除所有子节点
        while (this->parentItem->childCount() > 0) {
            QTreeWidgetItem* child = this->parentItem->takeChild(0); // 移除第一个子节点
            delete child; // 释放内存
        }
    }
    this->dateItems.clear(); // 同步清空存储子项的列表
}

void Mainwidget::clearPictureData()
{
    for (auto p : this->picturelist) {
        delete p;
    }
    this->picturelist.clear();
    this->pictureItems.clear();
    this->ui->listWidget->clear();
}

void Mainwidget::clearPictureTree()
{
    this->ui->treeWidget->clear();
    this->dateItems1.clear();
    this->parentItem1 = nullptr;
}

void Mainwidget::showPicturePreview(const QString &imagePath, const QString &title)
{
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "图片预览失败", "无法加载图片: " + imagePath);
        return;
    }

    QDialog *dialog = new QDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(title);
    dialog->resize(1100, 760);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    QScrollArea *scrollArea = new QScrollArea(dialog);
    QLabel *imageLabel = new QLabel(scrollArea);
    imageLabel->setAlignment(Qt::AlignCenter);
    // 单击预览时默认放大到接近屏幕可视区域
    QScreen *screen = QGuiApplication::primaryScreen();
    QSize targetSize = screen ? screen->availableGeometry().size() * 0.85 : QSize(1100, 760);
    imageLabel->setPixmap(pixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setScaledContents(false);

    scrollArea->setWidget(imageLabel);
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);

    dialog->exec();
}

void Mainwidget::listwidget()
{
    ui->listWidget_2->setViewMode(QListView::IconMode);
    ui->listWidget_2->setMovement(QListView::Static);

    // 设置网格布局参数
    ui->listWidget_2->setGridSize(QSize(220, 260));
    ui->listWidget_2->setIconSize(QSize(180, 180));
    ui->listWidget_2->setSpacing(14);

    // 设置文字对齐和换行
    ui->listWidget_2->setWordWrap(true);
    ui->listWidget_2->setResizeMode(QListView::Adjust);
    ui->listWidget_2->setTextElideMode(Qt::ElideRight);

    // 自定义样式表
    ui->listWidget_2->setStyleSheet(R"(
        QListWidget {
            background: #f5f5f7;
            border-radius: 8px;
            padding: 12px;
        }
        QListWidget::item {
            width: 200px;
            height: 240px;
            border: 1px solid #e0e0e0;
            border-radius: 8px;
            background: white;
            margin: 6px;
            padding: 8px;
        }
        QListWidget::item:hover {
            background: #f8f9fa;
            border-color: #007AFF;
        }
        QListWidget::item:selected {
            background: #e3f2fd;
            border-color: #2196F3;
        }
        QListWidget::item QLabel#textLabel {
            font: 12px 'Microsoft YaHei';
            color: #333;
            padding: 4px;
            text-align: center;
        }
    )");

    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setMovement(QListView::Static);
    ui->listWidget->setGridSize(QSize(220, 260));
    ui->listWidget->setIconSize(QSize(180, 180));
    ui->listWidget->setSpacing(14);
    ui->listWidget->setWordWrap(true);
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setTextElideMode(Qt::ElideRight);
    ui->listWidget->setStyleSheet(R"(
        QListWidget {
            background: #f5f5f7;
            border-radius: 8px;
            padding: 12px;
        }
        QListWidget::item {
            width: 200px;
            height: 240px;
            border: 1px solid #e0e0e0;
            border-radius: 8px;
            background: white;
            margin: 6px;
            padding: 8px;
        }
        QListWidget::item:hover {
            background: #f8f9fa;
            border-color: #007AFF;
        }
        QListWidget::item:selected {
            background: #e3f2fd;
            border-color: #2196F3;
        }
    )");
}

void Mainwidget::on_radioButton_4_clicked()
{
    this->videolist.clear(); // 发起新请求前清空旧数据
    this->ui->listWidget_2->clear();
    char sendbuf[8192];
    GET_VIDEO_REQ get_video_req;
    get_video_req.from=0;
    get_video_req.to=5;
    get_video_req.type=0;
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    strcpy(get_video_req.time,timestamp.toUtf8());

    HEAD head;
    head.data_len=sizeof(GET_VIDEO_REQ );
    head.service_type=GET_VIDEO_LIST;


    // 封装数据

    memcpy(sendbuf,&head,sizeof(HEAD));
    memcpy(sendbuf+sizeof(HEAD),&get_video_req,head.data_len);
    crcValidator.GenerateChecksum(sendbuf,sizeof(HEAD)+sizeof(GET_VIDEO_REQ));
    Socketmode::getInstance()->sendmsg(sendbuf,sizeof(HEAD)+sizeof(GET_VIDEO_REQ));
}

void Mainwidget::on_radioButton_5_clicked()
{
    this->videolist.clear(); // 发起新请求前清空旧数据
    this->ui->listWidget_2->clear();
    char sendbuf[8192];
    GET_VIDEO_REQ get_video_req;
    get_video_req.from=0;
    get_video_req.to=14;
    get_video_req.type=1;
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    strcpy(get_video_req.time,timestamp.toUtf8());

    HEAD head;
    head.data_len=sizeof(GET_VIDEO_REQ );
    head.service_type=GET_VIDEO_LIST;



    // 封装数据

    memcpy(sendbuf,&head,sizeof(HEAD));
    memcpy(sendbuf+sizeof(HEAD),&get_video_req,head.data_len);
    crcValidator.GenerateChecksum(sendbuf,sizeof(HEAD)+sizeof(GET_VIDEO_REQ));
    int res=Socketmode::getInstance()->sendmsg(sendbuf,sizeof(HEAD)+sizeof(GET_VIDEO_REQ));
     qDebug() << res<<endl;
}

void Mainwidget::on_treeWidget_2_itemClicked(QTreeWidgetItem *item, int column)
{
    QString itemText = item->text(0);  // 提取点击项的文本
       if (itemText.isEmpty()) {
           qDebug() << "Item text is empty!";
           return;
       }
    char sendbuf[8192];
    GET_VIDEO_REQ get_video_req;
    get_video_req.from=0;
    get_video_req.to=14;
    get_video_req.type=2;

    strcpy(get_video_req.time,itemText.toUtf8());
        qDebug()<<get_video_req.time<<"720"<<endl;
    HEAD head;
    head.data_len=sizeof(GET_VIDEO_REQ );
    head.service_type=GET_VIDEO_LIST;



    // 封装数据

    memcpy(sendbuf,&head,sizeof(HEAD));
    memcpy(sendbuf+sizeof(HEAD),&get_video_req,head.data_len);
    crcValidator.GenerateChecksum(sendbuf,sizeof(HEAD)+sizeof(GET_VIDEO_REQ));
    Socketmode::getInstance()->sendmsg(sendbuf,sizeof(HEAD)+sizeof(GET_VIDEO_REQ));
}

void Mainwidget::sendfilesuccess()
{
         QMessageBox::information(this,"文件发送成功","成功");
}

void Mainwidget::sendfilewarn()
{
        QMessageBox::information(this,"文件发送失败","请重试");
}

void Mainwidget::sendvideosuccess(QString file)
{
    QMessageBox::information(this,file+"视频信息发送成功","视频信息");
}

void Mainwidget::sendvideowarn()
{
     QMessageBox::information(this,"视频信息发送失败","请重试");
}

void Mainwidget::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    for (const auto& videoItem : videoItems)
       {
           if (item == videoItem)
           {
               int index = videoItems.indexOf(videoItem);
               if (index >= 0 && index < this->videolist.size())
               {
                   QString str = this->videolist.at(index)->video_name;
                   QString newStr = str.left(str.length() - 4);
                   QList<settingfile> configs  = readConfigfile("./settingfile/parking_system.conf");
                  savePath= QString::fromUtf8(configs.first().video_path.c_str());
                   qDebug() <<savePath+"/"+str<<"-------------MainWidget::on_listWidget_itemClicked1088";
                    this->c=new VideoPlayer(nullptr,savePath+"/"+str);
                    this->c->show();


               }
               break; // 找到匹配项后退出循环
           }
       }
}


void Mainwidget::on_radioButton_2_clicked()
{
    clearPictureData();
    clearPictureTree();
    char sendbuf[8192];
    GET_PICTURE_REQ get_picture_req;
    get_picture_req.from=0;
    get_picture_req.to=MAX_PICTURE - 1;
    get_picture_req.type=0; // 0 按月
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    strcpy(get_picture_req.time,timestamp.toUtf8());

    HEAD head;
    head.data_len=sizeof(GET_PICTURE_REQ );
    head.service_type=GET_PICTURE_LIST;



    // 封装数据

    memcpy(sendbuf,&head,sizeof(HEAD));
    memcpy(sendbuf+sizeof(HEAD),&get_picture_req,head.data_len);
    crcValidator.GenerateChecksum(sendbuf,sizeof(HEAD)+sizeof(GET_PICTURE_REQ));
    Socketmode::getInstance()->sendmsg(sendbuf,sizeof(HEAD)+sizeof(GET_PICTURE_REQ));
    qDebug()<<"941"<<endl;
}

void Mainwidget::on_radioButton_3_clicked()
{
    clearPictureData();
    clearPictureTree();
    char sendbuf[8192];
    GET_PICTURE_REQ get_picture_req;
    get_picture_req.from=0;
    get_picture_req.to=MAX_PICTURE - 1;
    get_picture_req.type=1; // 1 按天
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    strcpy(get_picture_req.time,timestamp.toUtf8());

    HEAD head;
    head.data_len=sizeof(GET_PICTURE_REQ );
    head.service_type=GET_PICTURE_LIST;



    // 封装数据

    memcpy(sendbuf,&head,sizeof(HEAD));
    memcpy(sendbuf+sizeof(HEAD),&get_picture_req,head.data_len);
    crcValidator.GenerateChecksum(sendbuf,sizeof(HEAD)+sizeof(GET_PICTURE_REQ));
    Socketmode::getInstance()->sendmsg(sendbuf,sizeof(HEAD)+sizeof(GET_PICTURE_REQ));
    qDebug()<<"966"<<endl;
}

void Mainwidget::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QString itemText = item->text(0);  // 提取点击项的文本
       if (itemText.isEmpty()) {
           qDebug() << "Item text is empty!";
           return;
       }
       char sendbuf[8192];
       GET_PICTURE_REQ get_picture_req;
       get_picture_req.from=0;
       get_picture_req.to=MAX_PICTURE - 1;
       get_picture_req.type=2; // 2 按你原来传入的方式（日期点击）
       strcpy(get_picture_req.time,itemText.toUtf8());

       HEAD head;
       head.data_len=sizeof(GET_PICTURE_REQ );
       head.service_type=GET_PICTURE_LIST;



       // 封装数据

       memcpy(sendbuf,&head,sizeof(HEAD));
       memcpy(sendbuf+sizeof(HEAD),&get_picture_req,head.data_len);
       crcValidator.GenerateChecksum(sendbuf,sizeof(HEAD)+sizeof(GET_PICTURE_REQ));
       Socketmode::getInstance()->sendmsg(sendbuf,sizeof(HEAD)+sizeof(GET_PICTURE_REQ));
}

void Mainwidget::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if (!item) {
        return;
    }

    QString imagePath = item->data(Qt::UserRole).toString();
    if (imagePath.isEmpty()) {
        QList<settingfile> configs = readConfigfile("./settingfile/parking_system.conf");
        if (configs.isEmpty()) {
            QMessageBox::warning(this, "图片预览失败", "配置文件为空，无法定位图片路径");
            return;
        }
        QString imageRoot = QString::fromUtf8(configs.first().image_path.c_str());
        imagePath = QDir(imageRoot).filePath(item->text());
    }

    showPicturePreview(imagePath, item->text());
}
