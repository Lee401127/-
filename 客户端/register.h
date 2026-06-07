#ifndef REGISTER_H
#define REGISTER_H

#include"protecol.h"
#include"socketmode.h"
#include"encryptiondecryption.h"
#include <QWidget>
#include<QMessageBox>
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
signals:
    QString pwdtext(QString pwd);
    void registery();
    void registern();
    void backlogin();
private slots:


    void passpwd(QString pwd);

    void codeget(QString code);
    void registerno();
    void phonebeenused();
    void sendno();

    void on_pushButton_clicked();

    void on_cancle_pushButton_clicked();

    void on_code_pushButton_clicked();

private:
    Ui::Register *ui;
    bool isclicked;
     int kind;
    EncryptionDecryption crcValidator;
};

#endif // REGISTER_H
