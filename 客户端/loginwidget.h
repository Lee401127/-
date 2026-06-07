#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include<QMessageBox>
#include <QWidget>
#include"register.h"
#include"register.h"
#include"protecol.h"
#include"socketmode.h"
#include"mainwidget.h"
#include"mainwidget1.h"
#include"old.h"
#include"encryptiondecryption.h"
#include<QCryptographicHash>
namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();



private slots:
    void on_register_pushButton_clicked();
    void turn(QString pwd);
    void back();
    void on_login_pushButton_clicked();
    void codeget(QString code);

    void login1(QString phone);
    void login2(QString phone);
    void login3(QString phone);
    void usernoexit();
    void pwdwarn();
    void codewarn();
    void loginRoleMismatch(QString msg);
    void connectwarn();

    void sendno();
    void onChildLogout();
    void on_code_pushButton_clicked();
private:
    void init_connect();
    void logincode();
    int kind;
    QString md5Encrypt(const QString &input);
    Ui::LoginWidget *ui;
    Register *registers;
    Mainwidget *main;
    MainWidget1 *main1;
    Old *old;
    EncryptionDecryption crcValidator;
};

#endif // LOGINWIDGET_H
