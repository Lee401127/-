#ifndef MAINWIDGET1_H
#define MAINWIDGET1_H
#include"socketmode.h"
#include <QWidget>
#include<QTimer>
#include"protecol.h"
#include<QMessageBox>
#include"encryptiondecryption.h"
#include <QTableWidget>
namespace Ui {
class MainWidget1;
}

class MainWidget1 : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget1(QWidget *parent = nullptr);
    ~MainWidget1();
 void setuserid(QString userid);
  void updateTime();
  void init_connect1();
  void setupCallRecordTab();
  void requestCallRecordList();
private slots:

  void onGetOldListSuccess(const Eld &old);
  void onGetOldListWarn(const QString &errMsg);
  void onGetOldListFinished();  // 可选，用于重置标志
 void on_comboBox_2_currentIndexChanged(int index);

 void on_pushButton_3_clicked();

 void on_pushButton_9_clicked();

 void on_comboBox_7_currentIndexChanged(int index);

 void on_pushButton_10_clicked();

 void on_pushButton_4_clicked();

 void on_pushButton_clicked();

 void on_comboBox_5_currentIndexChanged(int index);

 void on_pushButton_5_clicked();
void onComboIndexChanged(int index);
 void on_pushButton_16_clicked();
 void on_pushButton_15_clicked();
 // 老人信息
  void onElderInfoSuccess();
  void onElderInfoFailed();
  void onElderInfoQuerySuccess(const QString &name, int age, const QString &gender,
                               const QString &recordTime, const QString &contact, const QString &remark);
  void onElderInfoQueryFailed(const QString &errMsg);
  void onBloodQueryRow(int row, int systolic, int diastolic, const QString &measureTime, const QString &remark);
  void onBloodQueryFailed(const QString &errMsg);
  void onMedicineQueryRow(int row, const QString &name, const QString &dosage,
                          const QString &recordTime, const QString &usage, const QString &remark);
  void onMedicineQueryFailed(const QString &errMsg);
  void onActivityQueryRow(int row, const QString &type, const QString &startTime, const QString &endTime);
  void onActivityQueryFailed(const QString &errMsg);

  // 血压记录
  void onBloodPressureSuccess();
  void onBloodPressureFailed();
  void onBloodPressureSuccessDetail(int recordId);
  void onBloodPressureFailedDetail(const QString &errMsg);

  // 药品记录
  void onMedicineSuccess();
  void onMedicineFailed();
  void onMedicineSuccessDetail(int recordId);
  void onMedicineFailedDetail(const QString &errMsg);

  // 活动记录
  void onActivitySuccess();
  void onActivityFailed();
  void onActivitySuccessDetail(int recordId);
  void onActivityFailedDetail(const QString &errMsg);
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_11_clicked();
  void on_pushButton_12_clicked();
  void on_pushButton_13_clicked();
  void on_pushButton_14_clicked();
  void on_pushButton_2_clicked();

  void onCallRecordQueryRow(int callId, QString elderPhone, int type, QString time, QString remark);
  void onCallRecordQueryFailed(const QString &errMsg);

signals:
  void logoutRequested();

private:
    Ui::MainWidget1 *ui;
    QString userid;
    QString formattedTime;//系统时间
    bool m_firstOldReceived;  // 标志是否已接收到第一个老人
    EncryptionDecryption crcValidator;
    QString phone1;
    QWidget *m_callRecordPage;
    QTableWidget *m_callRecordTable;
};

#endif // MAINWIDGET1_H

