#ifndef OLD_H
#define OLD_H

#include <QWidget>
#include "socketmode.h"
#include "encryptiondecryption.h"

namespace Ui {
class Old;
}

class Old : public QWidget
{
    Q_OBJECT

public:
    explicit Old(QWidget *parent = nullptr);
    ~Old();
    void setuserid(QString userid);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_9_clicked();
    void onCallReportOk(int callId);
    void onCallReportFail(const QString &msg);

signals:
    void logoutRequested();

private:
    Ui::Old *ui;
    QString userid;
    EncryptionDecryption crcValidator;
};

#endif // OLD_H
