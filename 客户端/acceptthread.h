
#ifndef ACCEPTTHREAD_H
#define ACCEPTTHREAD_H
#include <QThread>
#include <QMutex>
#include"encryptiondecryption.h"
#include "protecol.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<QDebug>
#include<QMessageBox>
class AcceptThread : public QThread {
    Q_OBJECT  // 添加Q_OBJECT宏以支持Qt特性
public:
    explicit AcceptThread(int socketfd, QObject *parent = nullptr);
  int getfd();
protected:
    void run();  // 使用override明确重写

private:
    int socketfd;
EncryptionDecryption crcValidator;
signals:

    void loginsuccess(QString);//登陆成功
    void nouser();//用户不存在
    void passwordwarn();//密码错误
    void codewarn();//验证码错误
    void loginsuccess1(QString);//登陆成功
    void loginsuccess2(QString);//登陆成功
    void loginRoleMismatch(QString msg);//所选角色与注册身份不一致（status6）
    void phonehasbeenused();//手机号已经存在
    void sendwarn();//短信验证码发送失败

    void registerswarn();//注册失败
    void password(QString);//注册成功
    void code(QString);//成功发送验证码
    void sendvideosuccess(QString);
    void sendvideowarn();
    void sendfilesuccess();//文件发送成功
    void sendfilewarn();//文件发送失败
    void sendpicturesuccess(QString);
    void sendpicturewarn();

    void getvideolistsuccess(Video*);
    void getDateTimeListSuccess(const QList<QString>);
    void getvideolistwarn();

    void getpicturelistsuccess(Picture*);
    void getpictureDateTimeListSuccess(const QList<QString>);
    void getpicturelistwarn();

    void getOldListSuccess(const Eld &old);
    void getOldListWarn(const QString &errMsg);
    void getOldListFinished();

    // 老人信息
      void elderInfoSuccess();
      void elderInfoFailed();
      void elderInfoQuerySuccess(const QString &name, int age, const QString &gender,
                                 const QString &recordTime, const QString &contact, const QString &remark);
      void elderInfoQueryFailed(const QString &errMsg);
      void bloodQueryRow(int row, int systolic, int diastolic, const QString &measureTime, const QString &remark);
      void bloodQueryFailed(const QString &errMsg);
      void medicineQueryRow(int row, const QString &name, const QString &dosage,
                            const QString &recordTime, const QString &usage, const QString &remark);
      void medicineQueryFailed(const QString &errMsg);
      void activityQueryRow(int row, const QString &type, const QString &startTime, const QString &endTime);
      void activityQueryFailed(const QString &errMsg);

      // 血压记录
      void bloodPressureSuccess();
      void bloodPressureFailed();
      void bloodPressureSuccessDetail(int recordId);
      void bloodPressureFailedDetail(const QString &errMsg);

      // 药品记录
      void medicineSuccess();
      void medicineFailed();
      void medicineSuccessDetail(int recordId);
      void medicineFailedDetail(const QString &errMsg);

      // 活动记录
      void activitySuccess();
      void activityFailed();
      void activitySuccessDetail(int recordId);
      void activityFailedDetail(const QString &errMsg);

      void callRecordReportSuccess(int callId);
      void callRecordReportFailed(const QString &errMsg);
      void callRecordQueryRow(int callId, const QString &elderPhone, int type, const QString &time, const QString &remark);
      void callRecordQueryFailed(const QString &errMsg);
};
#endif // ACCEPTTHREAD_H
