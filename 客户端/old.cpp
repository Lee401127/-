#include "old.h"
#include "ui_old.h"
#include <QMessageBox>
#include <cstring>

Old::Old(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Old)
{
    ui->setupUi(this);
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(callRecordReportSuccess(int)),
            this, SLOT(onCallReportOk(int)), Qt::UniqueConnection);
    connect(Socketmode::getInstance()->acceptthread, SIGNAL(callRecordReportFailed(QString)),
            this, SLOT(onCallReportFail(QString)), Qt::UniqueConnection);
}

Old::~Old()
{
    delete ui;
}

void Old::setuserid(QString userid)
{
    this->userid = userid;
}

void Old::on_pushButton_clicked()
{
    if (userid.trimmed().isEmpty()) {
        QMessageBox::warning(this, QString::fromUtf8("提示"), QString::fromUtf8("未登录，无法呼叫"));
        return;
    }
    char buf[8192] = {0};
    HEAD head = {};
    head.service_type = CALL_RECORD_REPORT;
    head.data_len = sizeof(CALL_RECORD_REPORT_REQ);
    CALL_RECORD_REPORT_REQ req = {0};
    strncpy(req.elder_phone, userid.toUtf8().constData(), sizeof(req.elder_phone) - 1);
    req.call_type = 0;
    strncpy(req.remark, QString::fromUtf8("一键呼叫").toUtf8().constData(), sizeof(req.remark) - 1);
    memcpy(buf, &head, sizeof(HEAD));
    memcpy(buf + sizeof(HEAD), &req, sizeof(CALL_RECORD_REPORT_REQ));
    crcValidator.GenerateChecksum(buf, sizeof(HEAD) + sizeof(CALL_RECORD_REPORT_REQ));
    Socketmode::getInstance()->sendmsg(buf, sizeof(HEAD) + sizeof(CALL_RECORD_REPORT_REQ));
}

void Old::onCallReportOk(int callId)
{
    Q_UNUSED(callId);
    QMessageBox::information(this, QString::fromUtf8("呼叫"), QString::fromUtf8("已通知服务器，家属可在呼叫记录中查看。"));
}

void Old::onCallReportFail(const QString &msg)
{
    QMessageBox::warning(this, QString::fromUtf8("呼叫失败"), msg.isEmpty() ? QString::fromUtf8("服务器保存失败") : msg);
}

void Old::on_pushButton_9_clicked()
{
    this->userid.clear();
    this->hide();
    emit logoutRequested();
}
