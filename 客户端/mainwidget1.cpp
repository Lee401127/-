#include "mainwidget1.h"
#include "ui_mainwidget1.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <cstring>
#include <QHeaderView>
MainWidget1::MainWidget1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget1)
{   m_firstOldReceived = false;
    m_callRecordPage = nullptr;
    m_callRecordTable = nullptr;
    QTimer* timeUpdateTimer = new QTimer(this);
    ui->setupUi(this);
    connect(timeUpdateTimer, &QTimer::timeout, this, &MainWidget1::updateTime);
    timeUpdateTimer->start(1000);
    init_connect1();
    setupCallRecordTab();
}

MainWidget1::~MainWidget1()
{
    delete ui;
}

void MainWidget1::setuserid(QString userid)
{
    this->userid=userid;
}

void MainWidget1::updateTime()
{

    QDateTime currentTime = QDateTime::currentDateTime();
    formattedTime = currentTime.toString("yyyy-MM-dd HH:mm:ss");
    this->ui->systemtime_label->setText("当前系统时间："+formattedTime);
}

void MainWidget1::init_connect1()
{


    connect(Socketmode::getInstance()->acceptthread, SIGNAL(getOldListSuccess(const Eld&)),
            this, SLOT(onGetOldListSuccess(const Eld&)));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(getOldListWarn(QString)),
            this, SLOT(onGetOldListWarn(QString)));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(getOldListFinished()),
            this, SLOT(onGetOldListFinished()));
    // 老人信息
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(elderInfoSuccess()),
            this, SLOT(onElderInfoSuccess()));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(elderInfoFailed()),
            this, SLOT(onElderInfoFailed()));
    connect(Socketmode::getInstance()->acceptthread,
            SIGNAL(elderInfoQuerySuccess(QString,int,QString,QString,QString,QString)),
            this,
            SLOT(onElderInfoQuerySuccess(QString,int,QString,QString,QString,QString)));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(elderInfoQueryFailed(QString)),
            this, SLOT(onElderInfoQueryFailed(QString)));
    connect(Socketmode::getInstance()->acceptthread,
            SIGNAL(bloodQueryRow(int,int,int,QString,QString)),
            this,
            SLOT(onBloodQueryRow(int,int,int,QString,QString)));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(bloodQueryFailed(QString)),
            this, SLOT(onBloodQueryFailed(QString)));
    connect(Socketmode::getInstance()->acceptthread,
            SIGNAL(medicineQueryRow(int,QString,QString,QString,QString,QString)),
            this,
            SLOT(onMedicineQueryRow(int,QString,QString,QString,QString,QString)));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(medicineQueryFailed(QString)),
            this, SLOT(onMedicineQueryFailed(QString)));
    connect(Socketmode::getInstance()->acceptthread,
            SIGNAL(activityQueryRow(int,QString,QString,QString)),
            this,
            SLOT(onActivityQueryRow(int,QString,QString,QString)));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(activityQueryFailed(QString)),
            this, SLOT(onActivityQueryFailed(QString)));

    // 血压记录
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(bloodPressureSuccess()),
            this, SLOT(onBloodPressureSuccess()));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(bloodPressureFailed()),
            this, SLOT(onBloodPressureFailed()));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(bloodPressureSuccessDetail(int)),
            this, SLOT(onBloodPressureSuccessDetail(int)));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(bloodPressureFailedDetail(QString)),
            this, SLOT(onBloodPressureFailedDetail(QString)));

    // 药品记录
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(medicineSuccess()),
            this, SLOT(onMedicineSuccess()));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(medicineFailed()),
            this, SLOT(onMedicineFailed()));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(medicineSuccessDetail(int)),
            this, SLOT(onMedicineSuccessDetail(int)));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(medicineFailedDetail(QString)),
            this, SLOT(onMedicineFailedDetail(QString)));

    // 活动记录
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(activitySuccess()),
            this, SLOT(onActivitySuccess()));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(activityFailed()),
            this, SLOT(onActivityFailed()));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(activitySuccessDetail(int)),
            this, SLOT(onActivitySuccessDetail(int)));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(activityFailedDetail(QString)),
            this, SLOT(onActivityFailedDetail(QString)));
    // 在构造函数中连接信号
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWidget1::onComboIndexChanged);

    connect(Socketmode::getInstance()->acceptthread,
            SIGNAL(callRecordQueryRow(int,QString,int,QString,QString)),
            this,
            SLOT(onCallRecordQueryRow(int,QString,int,QString,QString)));
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(callRecordQueryFailed(QString)),
            this, SLOT(onCallRecordQueryFailed(QString)));

}

void MainWidget1::setupCallRecordTab()
{
    m_callRecordPage = new QWidget(ui->page_6);
    QVBoxLayout *vl = new QVBoxLayout(m_callRecordPage);
    m_callRecordTable = new QTableWidget(0, 5, m_callRecordPage);
    m_callRecordTable->setHorizontalHeaderLabels(
        QStringList() << QString::fromUtf8("编号") << QString::fromUtf8("老人手机")
                      << QString::fromUtf8("类型") << QString::fromUtf8("时间") << QString::fromUtf8("备注"));
    m_callRecordTable->setShowGrid(true);
       m_callRecordTable->setGridStyle(Qt::SolidLine);
       m_callRecordTable->setAlternatingRowColors(true);
       m_callRecordTable->horizontalHeader()->setStretchLastSection(true);
       m_callRecordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
       m_callRecordTable->verticalHeader()->setVisible(false);
       m_callRecordTable->setMinimumHeight(280);
    QPushButton *refreshBtn = new QPushButton(QString::fromUtf8("刷新呼叫记录"), m_callRecordPage);
    vl->addWidget(m_callRecordTable);
    vl->addWidget(refreshBtn);
    m_callRecordPage->setLayout(vl);
    ui->stackedWidget_4->addWidget(m_callRecordPage);
    ui->comboBox_5->addItem(QString::fromUtf8("呼叫记录"));
    connect(refreshBtn, &QPushButton::clicked, this, &MainWidget1::requestCallRecordList);
}

void MainWidget1::requestCallRecordList()
{
    QString elderPhone = ui->lineEdit_7->text().trimmed();
    if (elderPhone.isEmpty())
        elderPhone = phone1;
    if (userid.trimmed().isEmpty() || elderPhone.trimmed().isEmpty()) {
        QMessageBox::warning(this, QString::fromUtf8("提示"),
 QString::fromUtf8("请先登录，并在上方填写或选择老人电话"));
        return;
    }
    if (m_callRecordTable)
        m_callRecordTable->setRowCount(0);
    char buf[8192] = {0};
    HEAD head = {};
    head.service_type = CALL_RECORD_QUERY;
    head.data_len = sizeof(CALL_RECORD_QUERY_REQ);
    CALL_RECORD_QUERY_REQ req = {0};
    strncpy(req.family_phone, userid.toUtf8().constData(), sizeof(req.family_phone) - 1);
    strncpy(req.elder_phone, elderPhone.toUtf8().constData(), sizeof(req.elder_phone) - 1);
    req.from = 0;
    req.to = MAX_CALL_RECORD;
    memcpy(buf, &head, sizeof(HEAD));
    memcpy(buf + sizeof(HEAD), &req, sizeof(CALL_RECORD_QUERY_REQ));
    crcValidator.GenerateChecksum(buf, sizeof(HEAD) + sizeof(CALL_RECORD_QUERY_REQ));
    Socketmode::getInstance()->sendmsg(buf, sizeof(HEAD) + sizeof(CALL_RECORD_QUERY_REQ));
}

void MainWidget1::onCallRecordQueryRow(int callId, QString elderPhone, int type, QString time, QString remark)
{
    if (!m_callRecordTable)
        return;
    const int row = m_callRecordTable->rowCount();
    m_callRecordTable->insertRow(row);
    m_callRecordTable->setItem(row, 0, new QTableWidgetItem(QString::number(callId)));
    m_callRecordTable->setItem(row, 1, new QTableWidgetItem(elderPhone));
    const QString typeStr = (type == 1) ? QString::fromUtf8("紧急") : QString::fromUtf8("普通");
    m_callRecordTable->setItem(row, 2, new QTableWidgetItem(typeStr));
    m_callRecordTable->setItem(row, 3, new QTableWidgetItem(time));
    m_callRecordTable->setItem(row, 4, new QTableWidgetItem(remark));
}

void MainWidget1::onCallRecordQueryFailed(const QString &errMsg)
{
    if (m_callRecordTable)
        m_callRecordTable->setRowCount(0);
    QMessageBox::warning(this, QString::fromUtf8("呼叫记录"),
                           errMsg.trimmed().isEmpty() ? QString::fromUtf8("查询失败") : errMsg);
}

void MainWidget1::onGetOldListSuccess(const Eld &old)
{
    if (!m_firstOldReceived) {
          ui->comboBox->clear();  // 第一次接收到时清空
          m_firstOldReceived = true;
      }
      QString phone = QString::fromLocal8Bit(old.phone);  // 根据实际编码选择 fromUtf8
      ui->comboBox->addItem(phone, QVariant(old.oldnum)); // 存储 ID 作为用户数据
      // 不在加载过程中反复覆盖 phone1，避免与用户实际选中项错位
      if (ui->comboBox->count() == 1) {
          ui->comboBox->setCurrentIndex(0);
          this->phone1 = ui->comboBox->currentText();
      }
}

void MainWidget1::onGetOldListWarn(const QString &errMsg)
{
    QMessageBox::warning(this, "获取老人信息失败", errMsg);
       m_firstOldReceived = false;  // 出错后重置标志，下次请求重新清空
}

void MainWidget1::onGetOldListFinished()
{
     m_firstOldReceived = false;  // 接收完毕后重置，以便下一次请求
}


void MainWidget1::on_comboBox_2_currentIndexChanged(int index)
{
        this->ui->stackedWidget_2->setCurrentIndex(index);
}

void MainWidget1::on_pushButton_3_clicked()
{
     this->ui->stackedWidget->setCurrentIndex(1);
}

void MainWidget1::on_pushButton_9_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}


void MainWidget1::on_comboBox_7_currentIndexChanged(int index)
{
    this->ui->stackedWidget_3->setCurrentIndex(index);
}

void MainWidget1::on_pushButton_10_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

void MainWidget1::on_pushButton_4_clicked()
{
     this->ui->stackedWidget->setCurrentIndex(2);
}

void MainWidget1::on_pushButton_clicked()
{
    char buf[8192]={0};
    GET_OLDLIST_REQ old_req={0};
    old_req.from=0;
    old_req.to=10;

    HEAD head={};
    head.service_type=  GET_OLD_LIST;
    head.data_len=sizeof(GET_OLDLIST_REQ);






    qDebug()<<"36"<<endl;
    memcpy(buf,&head,sizeof(HEAD));
    memcpy(buf+sizeof(HEAD),&old_req,head.data_len);
    crcValidator.GenerateChecksum(buf,sizeof(HEAD)+sizeof(GET_OLDLIST_REQ));
    Socketmode::getInstance()->sendmsg(buf,sizeof(HEAD)+sizeof(GET_OLDLIST_REQ));

}

void MainWidget1::on_pushButton_15_clicked()
{
    const QString phone = ui->lineEdit_7->text().trimmed();
    if (phone.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入要查询的老人电话");
        return;
    }

    char buf[8192] = {0};
    HEAD head = {};
    const int tab = ui->comboBox_5->currentIndex();
    if (tab == 0) {
        ElderInfoQueryReq req = {0};
        head.service_type = ELDERINFO_QUERY;
        head.data_len = sizeof(ElderInfoQueryReq);
        qstrncpy(req.phone, phone.toUtf8().constData(), sizeof(req.phone));
        ui->tableWidget->clearContents();
        memcpy(buf, &head, sizeof(HEAD));
        memcpy(buf + sizeof(HEAD), &req, sizeof(ElderInfoQueryReq));
        crcValidator.GenerateChecksum(buf, sizeof(HEAD) + sizeof(ElderInfoQueryReq));
        Socketmode::getInstance()->sendmsg(buf, sizeof(HEAD) + sizeof(ElderInfoQueryReq));
    }
    else if (tab == 1) {
        BloodPressureQueryReq req = {0};
        head.service_type = BLOODPRESSURERECORD_QUERY;
        head.data_len = sizeof(BloodPressureQueryReq);
        qstrncpy(req.phone, phone.toUtf8().constData(), sizeof(req.phone));
        ui->tableWidget_2->clearContents();
        memcpy(buf, &head, sizeof(HEAD));
        memcpy(buf + sizeof(HEAD), &req, sizeof(BloodPressureQueryReq));
        crcValidator.GenerateChecksum(buf, sizeof(HEAD) + sizeof(BloodPressureQueryReq));
        Socketmode::getInstance()->sendmsg(buf, sizeof(HEAD) + sizeof(BloodPressureQueryReq));
    }
    else if (tab == 2) {
        MedicineQueryReq req = {0};
        head.service_type = MEDICINERECORD_QUERY;
        head.data_len = sizeof(MedicineQueryReq);
        qstrncpy(req.phone, phone.toUtf8().constData(), sizeof(req.phone));
        ui->tableWidget_3->clearContents();
        memcpy(buf, &head, sizeof(HEAD));
        memcpy(buf + sizeof(HEAD), &req, sizeof(MedicineQueryReq));
        crcValidator.GenerateChecksum(buf, sizeof(HEAD) + sizeof(MedicineQueryReq));
        Socketmode::getInstance()->sendmsg(buf, sizeof(HEAD) + sizeof(MedicineQueryReq));
    }
    else if (tab == 3) {
        ActivityQueryReq req = {0};
        head.service_type = ACTIVITYRECORD_QUERY;
        head.data_len = sizeof(ActivityQueryReq);
        qstrncpy(req.phone, phone.toUtf8().constData(), sizeof(req.phone));
        ui->tableWidget_4->clearContents();
        memcpy(buf, &head, sizeof(HEAD));
        memcpy(buf + sizeof(HEAD), &req, sizeof(ActivityQueryReq));
        crcValidator.GenerateChecksum(buf, sizeof(HEAD) + sizeof(ActivityQueryReq));
        Socketmode::getInstance()->sendmsg(buf, sizeof(HEAD) + sizeof(ActivityQueryReq));
    }
    else if (tab == 4) {
        requestCallRecordList();
    }
}

void MainWidget1::on_comboBox_5_currentIndexChanged(int index)
{
    this->ui->stackedWidget_4->setCurrentIndex(index);
    if (index == 4)
        requestCallRecordList();
}

void MainWidget1::on_pushButton_5_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(3);
}

void MainWidget1::onComboIndexChanged(int index)
{
    if (index >= 0) {
            phone1 = ui->comboBox->itemText(index);

        }
}

void MainWidget1::on_pushButton_16_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}
void MainWidget1::onElderInfoSuccess() {
    QMessageBox::information(this, "成功", "老人信息保存成功");
    // 可刷新界面或进行其他成功后的操作
}

void MainWidget1::onElderInfoFailed() {
    QMessageBox::warning(this, "失败", "老人信息保存失败");
}

void MainWidget1::onElderInfoQuerySuccess(const QString &name, int age, const QString &gender,
                                          const QString &recordTime, const QString &contact, const QString &remark)
{
    QString genderText = "未知";
    if (gender.trimmed() == "1") genderText = "男";
    else if (gender.trimmed() == "2") genderText = "女";
    ui->tableWidget->clearContents();
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(age)));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(genderText));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(recordTime));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(name));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(contact));
    ui->tableWidget->setItem(0, 5, new QTableWidgetItem(remark));
}

void MainWidget1::onElderInfoQueryFailed(const QString &errMsg)
{
    ui->tableWidget->clearContents();
    const QString msg = errMsg.trimmed().isEmpty() ? "未查询到老人信息" : errMsg;
    QMessageBox::warning(this, "查询失败", msg);
}

void MainWidget1::onBloodQueryRow(int row, int systolic, int diastolic, const QString &measureTime, const QString &remark)
{
    if (row < 0 || row >= ui->tableWidget_2->rowCount()) return;
    ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(QString::number(systolic)));
    ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(QString::number(diastolic)));
    ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(measureTime));
    ui->tableWidget_2->setItem(row, 3, new QTableWidgetItem(remark));
}

void MainWidget1::onBloodQueryFailed(const QString &errMsg)
{
    ui->tableWidget_2->clearContents();
    const QString msg = errMsg.trimmed().isEmpty() ? "未查询到血压记录" : errMsg;
    QMessageBox::warning(this, "查询失败", msg);
}

void MainWidget1::onMedicineQueryRow(int row, const QString &name, const QString &dosage,
                                     const QString &recordTime, const QString &usage, const QString &remark)
{
    if (row < 0 || row >= ui->tableWidget_3->rowCount()) return;
    ui->tableWidget_3->setItem(row, 0, new QTableWidgetItem(name));
    ui->tableWidget_3->setItem(row, 1, new QTableWidgetItem(dosage));
    ui->tableWidget_3->setItem(row, 2, new QTableWidgetItem(recordTime));
    ui->tableWidget_3->setItem(row, 3, new QTableWidgetItem(usage));
    ui->tableWidget_3->setItem(row, 4, new QTableWidgetItem(remark));
}

void MainWidget1::onMedicineQueryFailed(const QString &errMsg)
{
    ui->tableWidget_3->clearContents();
    const QString msg = errMsg.trimmed().isEmpty() ? "未查询到药物记录" : errMsg;
    QMessageBox::warning(this, "查询失败", msg);
}

void MainWidget1::onActivityQueryRow(int row, const QString &type, const QString &startTime, const QString &endTime)
{
    if (row < 0 || row >= ui->tableWidget_4->rowCount()) return;
    QString typeText = "其他";
    if (type.trimmed() == "1") typeText = "起床";
    else if (type.trimmed() == "2") typeText = "用餐";
    else if (type.trimmed() == "3") typeText = "散步";
    else if (type.trimmed() == "4") typeText = "服药";
    ui->tableWidget_4->setItem(row, 0, new QTableWidgetItem(typeText));
    ui->tableWidget_4->setItem(row, 1, new QTableWidgetItem(startTime));
    ui->tableWidget_4->setItem(row, 2, new QTableWidgetItem(endTime));
}

void MainWidget1::onActivityQueryFailed(const QString &errMsg)
{
    ui->tableWidget_4->clearContents();
    const QString msg = errMsg.trimmed().isEmpty() ? "未查询到行为记录" : errMsg;
    QMessageBox::warning(this, "查询失败", msg);
}

void MainWidget1::onBloodPressureSuccess() {
    QMessageBox::information(this, "成功", "血压记录保存成功");
}

void MainWidget1::onBloodPressureFailed() {
    QMessageBox::warning(this, "失败", "血压记录保存失败");
}

void MainWidget1::onMedicineSuccess() {
    QMessageBox::information(this, "成功", "药品记录保存成功");
}

void MainWidget1::onMedicineFailed() {
    QMessageBox::warning(this, "失败", "药品记录保存失败");
}

void MainWidget1::onActivitySuccess() {
    QMessageBox::information(this, "成功", "活动记录保存成功");
}

void MainWidget1::onActivityFailed() {
    QMessageBox::warning(this, "失败", "活动记录保存失败");
}

void MainWidget1::onBloodPressureSuccessDetail(int recordId)
{
    if (recordId > 0) {
        QMessageBox::information(this, "成功", QString("血压记录保存成功，record_id=%1").arg(recordId));
    }
}

void MainWidget1::onBloodPressureFailedDetail(const QString &errMsg)
{
    if (!errMsg.trimmed().isEmpty()) {
        QMessageBox::warning(this, "失败", "血压记录保存失败：" + errMsg);
    }
}

void MainWidget1::onMedicineSuccessDetail(int recordId)
{
    if (recordId > 0) {
        QMessageBox::information(this, "成功", QString("药品记录保存成功，record_id=%1").arg(recordId));
    }
}

void MainWidget1::onMedicineFailedDetail(const QString &errMsg)
{
    if (!errMsg.trimmed().isEmpty()) {
        QMessageBox::warning(this, "失败", "药品记录保存失败：" + errMsg);
    }
}

void MainWidget1::onActivitySuccessDetail(int recordId)
{
    if (recordId > 0) {
        QMessageBox::information(this, "成功", QString("活动记录保存成功，record_id=%1").arg(recordId));
    }
}

void MainWidget1::onActivityFailedDetail(const QString &errMsg)
{
    if (!errMsg.trimmed().isEmpty()) {
        QMessageBox::warning(this, "失败", "活动记录保存失败：" + errMsg);
    }
}

void MainWidget1::on_pushButton_6_clicked()
{
    char buf[8192]={0};
    ElderInfoReq elderinfo_req={0};

    HEAD head={};
    head.service_type=ELDERINFO;
    head.data_len=sizeof(ElderInfoReq);
    QString AgeStr = ui->lineEdit->text().trimmed();
    elderinfo_req.elderInfo.age = AgeStr.toInt();
    QString NameStr = ui->lineEdit_3->text().trimmed();
    qstrncpy(elderinfo_req.elderInfo.name, NameStr.toUtf8().constData(), sizeof(elderinfo_req.elderInfo.name));
    QString remask = ui->lineEdit_2->text().trimmed();
    qstrncpy(elderinfo_req.elderInfo.remark, remask.toUtf8().constData(), sizeof(elderinfo_req.elderInfo.remark));
    QString contact= ui->lineEdit_8->text().trimmed();
    qstrncpy(elderinfo_req.elderInfo.contact, contact.toUtf8().constData(), sizeof(elderinfo_req.elderInfo.contact));
    const QString genderCode = QString::number(ui->comboBox_3->currentIndex() + 1);
    qstrncpy(elderinfo_req.elderInfo.gender, genderCode.toUtf8().constData(), sizeof(elderinfo_req.elderInfo.gender));
    QString recordTime = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    qstrncpy(elderinfo_req.elderInfo.recordTime, recordTime.toUtf8().constData(), sizeof(elderinfo_req.elderInfo.recordTime));
    elderinfo_req.type=0;

    QString selectedPhone = ui->comboBox->currentText().trimmed();
    if (selectedPhone.isEmpty()) {
        selectedPhone = this->phone1;
    }
    this->phone1 = selectedPhone;
    qstrncpy(elderinfo_req.phone, selectedPhone.toUtf8().constData(), sizeof(elderinfo_req.phone));
qDebug()<<"227"<<endl;
    memcpy(buf,&head,sizeof(HEAD));
    memcpy(buf+sizeof(HEAD),&elderinfo_req,head.data_len);
    crcValidator.GenerateChecksum(buf,sizeof(HEAD)+sizeof(ElderInfoReq));
    Socketmode::getInstance()->sendmsg(buf,sizeof(HEAD)+sizeof(ElderInfoReq));
}

void MainWidget1::on_pushButton_7_clicked()
{
    char buf[8192] = {0};
    BloodPressureReq bloodpressure_req = {0};

    HEAD head = {};
    head.service_type = BLOODPRESSURERECORD;
    head.data_len = sizeof(BloodPressureReq);

    // 收缩压 / 舒张压
    bloodpressure_req.bpRecord.systolic = ui->lineEdit_4->text().trimmed().toInt();
    bloodpressure_req.bpRecord.diastolic = ui->lineEdit_5->text().trimmed().toInt();

    // 测量时间（MySQL DATETIME 友好格式）
    QString measureTime = ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    qstrncpy(bloodpressure_req.bpRecord.measureTime,
             measureTime.toUtf8().constData(),
             sizeof(bloodpressure_req.bpRecord.measureTime));

    // 备注（注意协议里 remark 只有 20 字节）
    QString remark = ui->lineEdit_6->text().trimmed();
    qstrncpy(bloodpressure_req.bpRecord.remark,
             remark.toUtf8().constData(),
             sizeof(bloodpressure_req.bpRecord.remark));

    bloodpressure_req.type = 0; // 0:插入（按你协议约定）
    QString selectedPhone = ui->comboBox->currentText().trimmed();
    if (selectedPhone.isEmpty()) {
        selectedPhone = this->phone1;
    }
    this->phone1 = selectedPhone;
    qstrncpy(bloodpressure_req.phone,
             selectedPhone.toUtf8().constData(),
             sizeof(bloodpressure_req.phone));

    memcpy(buf, &head, sizeof(HEAD));
    memcpy(buf + sizeof(HEAD), &bloodpressure_req, head.data_len);
    crcValidator.GenerateChecksum(buf, sizeof(HEAD) + sizeof(BloodPressureReq));
    Socketmode::getInstance()->sendmsg(buf, sizeof(HEAD) + sizeof(BloodPressureReq));
}

void MainWidget1::on_pushButton_8_clicked()
{
    char buf[8192] = {0};
    MedicineReq med_req = {0};

    HEAD head = {};
    head.service_type = MEDICINERECORD;
    head.data_len = sizeof(MedicineReq);

    // 药品名称 / 剂量 / 用法 / 备注
    qstrncpy(med_req.medRecord.medicineName,
             ui->lineEdit_13->text().trimmed().toUtf8().constData(),
             sizeof(med_req.medRecord.medicineName));
    qstrncpy(med_req.medRecord.dosage,
             ui->lineEdit_14->text().trimmed().toUtf8().constData(),
             sizeof(med_req.medRecord.dosage));
    qstrncpy(med_req.medRecord.usage,
             ui->lineEdit_15->text().trimmed().toUtf8().constData(),
             sizeof(med_req.medRecord.usage));
    qstrncpy(med_req.medRecord.remark,
             ui->lineEdit_16->text().trimmed().toUtf8().constData(),
             sizeof(med_req.medRecord.remark));

    // 记录时间（MySQL DATETIME 友好格式）
    QString recordTime = ui->dateTimeEdit_5->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    qstrncpy(med_req.medRecord.recordTime,
             recordTime.toUtf8().constData(),
             sizeof(med_req.medRecord.recordTime));

    med_req.type = 0;
    QString selectedPhone = ui->comboBox->currentText().trimmed();
    if (selectedPhone.isEmpty()) {
        selectedPhone = this->phone1;
    }
    this->phone1 = selectedPhone;
    qstrncpy(med_req.phone, selectedPhone.toUtf8().constData(), sizeof(med_req.phone));

    memcpy(buf, &head, sizeof(HEAD));
    memcpy(buf + sizeof(HEAD), &med_req, head.data_len);
    crcValidator.GenerateChecksum(buf, sizeof(HEAD) + sizeof(MedicineReq));
    Socketmode::getInstance()->sendmsg(buf, sizeof(HEAD) + sizeof(MedicineReq));
}

void MainWidget1::on_pushButton_12_clicked()
{
    char buf[8192] = {0};
    ActivityReq act_req = {0};

    HEAD head = {};
    head.service_type = ACTIVITYRECORD;
    head.data_len = sizeof(ActivityReq);

    const int activityTypeCode = ui->comboBox_7->currentIndex() + 1; // 1~4
    const QString activityTypeStr = QString::number(activityTypeCode);
    qstrncpy(act_req.actRecord.activityType, activityTypeStr.toUtf8().constData(), sizeof(act_req.actRecord.activityType));
    QString startTime = ui->dateTimeEdit_6->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString endTime = ui->dateTimeEdit_7->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    qstrncpy(act_req.actRecord.startTime, startTime.toUtf8().constData(), sizeof(act_req.actRecord.startTime));
    qstrncpy(act_req.actRecord.nendTime, endTime.toUtf8().constData(), sizeof(act_req.actRecord.nendTime));

    act_req.type = 0;
    QString selectedPhone = ui->comboBox->currentText().trimmed();
    if (selectedPhone.isEmpty()) {
        selectedPhone = this->phone1;
    }
    this->phone1 = selectedPhone;
    qstrncpy(act_req.phone, selectedPhone.toUtf8().constData(), sizeof(act_req.phone));

    memcpy(buf, &head, sizeof(HEAD));
    memcpy(buf + sizeof(HEAD), &act_req, head.data_len);
    crcValidator.GenerateChecksum(buf, sizeof(HEAD) + sizeof(ActivityReq));
    Socketmode::getInstance()->sendmsg(buf, sizeof(HEAD) + sizeof(ActivityReq));
}

void MainWidget1::on_pushButton_13_clicked()
{
    char buf[8192] = {0};
    ActivityReq act_req = {0};

    HEAD head = {};
    head.service_type = ACTIVITYRECORD;
    head.data_len = sizeof(ActivityReq);

    const int activityTypeCode = ui->comboBox_7->currentIndex() + 1; // 1~4
    const QString activityTypeStr = QString::number(activityTypeCode);
    qstrncpy(act_req.actRecord.activityType, activityTypeStr.toUtf8().constData(), sizeof(act_req.actRecord.activityType));
    // UI: 开始时间 dateTimeEdit_9，结束时间 dateTimeEdit_8
    QString startTime = ui->dateTimeEdit_9->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString endTime = ui->dateTimeEdit_8->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    qstrncpy(act_req.actRecord.startTime, startTime.toUtf8().constData(), sizeof(act_req.actRecord.startTime));
    qstrncpy(act_req.actRecord.nendTime, endTime.toUtf8().constData(), sizeof(act_req.actRecord.nendTime));

    act_req.type = 0;
    QString selectedPhone = ui->comboBox->currentText().trimmed();
    if (selectedPhone.isEmpty()) {
        selectedPhone = this->phone1;
    }
    this->phone1 = selectedPhone;
    qstrncpy(act_req.phone, selectedPhone.toUtf8().constData(), sizeof(act_req.phone));

    memcpy(buf, &head, sizeof(HEAD));
    memcpy(buf + sizeof(HEAD), &act_req, head.data_len);
    crcValidator.GenerateChecksum(buf, sizeof(HEAD) + sizeof(ActivityReq));
    Socketmode::getInstance()->sendmsg(buf, sizeof(HEAD) + sizeof(ActivityReq));
}

void MainWidget1::on_pushButton_14_clicked()
{
    char buf[8192] = {0};
    ActivityReq act_req = {0};

    HEAD head = {};
    head.service_type = ACTIVITYRECORD;
    head.data_len = sizeof(ActivityReq);

    const int activityTypeCode = ui->comboBox_7->currentIndex() + 1; // 1~4
    const QString activityTypeStr = QString::number(activityTypeCode);
    qstrncpy(act_req.actRecord.activityType, activityTypeStr.toUtf8().constData(), sizeof(act_req.actRecord.activityType));
    // UI: 开始时间 dateTimeEdit_11，结束时间 dateTimeEdit_10
    QString startTime = ui->dateTimeEdit_11->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString endTime = ui->dateTimeEdit_10->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    qstrncpy(act_req.actRecord.startTime, startTime.toUtf8().constData(), sizeof(act_req.actRecord.startTime));
    qstrncpy(act_req.actRecord.nendTime, endTime.toUtf8().constData(), sizeof(act_req.actRecord.nendTime));

    act_req.type = 0;
    QString selectedPhone = ui->comboBox->currentText().trimmed();
    if (selectedPhone.isEmpty()) {
        selectedPhone = this->phone1;
    }
    this->phone1 = selectedPhone;
    qstrncpy(act_req.phone, selectedPhone.toUtf8().constData(), sizeof(act_req.phone));

    memcpy(buf, &head, sizeof(HEAD));
    memcpy(buf + sizeof(HEAD), &act_req, head.data_len);
    crcValidator.GenerateChecksum(buf, sizeof(HEAD) + sizeof(ActivityReq));
    Socketmode::getInstance()->sendmsg(buf, sizeof(HEAD) + sizeof(ActivityReq));
}

void MainWidget1::on_pushButton_11_clicked()
{
    char buf[8192] = {0};
    ActivityReq act_req = {0};

    HEAD head = {};
    head.service_type = ACTIVITYRECORD;
    head.data_len = sizeof(ActivityReq);

    const int activityTypeCode = ui->comboBox_7->currentIndex() + 1; // 1~4
    const QString activityTypeStr = QString::number(activityTypeCode);
    qstrncpy(act_req.actRecord.activityType, activityTypeStr.toUtf8().constData(), sizeof(act_req.actRecord.activityType));
    // UI: 服药开始时间 dateTimeEdit_13，服药结束时间 dateTimeEdit_12
    QString startTime = ui->dateTimeEdit_13->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString endTime = ui->dateTimeEdit_12->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    qstrncpy(act_req.actRecord.startTime, startTime.toUtf8().constData(), sizeof(act_req.actRecord.startTime));
    qstrncpy(act_req.actRecord.nendTime, endTime.toUtf8().constData(), sizeof(act_req.actRecord.nendTime));

    act_req.type = 0;
    QString selectedPhone = ui->comboBox->currentText().trimmed();
    if (selectedPhone.isEmpty()) {
        selectedPhone = this->phone1;
    }
    this->phone1 = selectedPhone;
    qstrncpy(act_req.phone, selectedPhone.toUtf8().constData(), sizeof(act_req.phone));

    memcpy(buf, &head, sizeof(HEAD));
    memcpy(buf + sizeof(HEAD), &act_req, head.data_len);
    crcValidator.GenerateChecksum(buf, sizeof(HEAD) + sizeof(ActivityReq));
    Socketmode::getInstance()->sendmsg(buf, sizeof(HEAD) + sizeof(ActivityReq));
}

void MainWidget1::on_pushButton_2_clicked()
{
    this->userid.clear();
    this->hide();
    emit logoutRequested();
}
