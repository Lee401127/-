#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <Qt>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    this->registers=new Register;
    this->main=new Mainwidget;
    this->main1=new MainWidget1;
    this->old=new Old;
     int kind=0;
    ui->setupUi(this);
    this->init_connect();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}


void LoginWidget::on_register_pushButton_clicked()
{
    this->hide();
    this->registers->show();
}
void LoginWidget::turn(QString pwd)
{
    this->registers->hide();
    this->show();
    this->ui->pwd_lineEdit->setText(pwd);
}

void LoginWidget::back()
{
    this->registers->hide();
    this->show();
}

void LoginWidget::on_login_pushButton_clicked()
{
    QString id=ui->account_lineEdit->text().trimmed();
    QString pwd=ui->pwd_lineEdit->text().trimmed();
    QString code=ui->code_lineEdit->text().trimmed();
    QString encryptedPwd = md5Encrypt(pwd);
    int currentIndex = ui->comboBox->currentIndex();
    if (currentIndex == 0) {
        kind = 0;
    } else if (currentIndex == 1) {
        kind = 1;
    } else if (currentIndex == 2) {
        kind = 2;
    }
    if(id.isEmpty()||pwd.isEmpty()||code.isEmpty())
    {
        QMessageBox::information(this,"登陆失败","账号密码或验证码为空");
         return;
    }
    else
    {
        if (!Socketmode::getInstance()->isConnected()) {
            QMessageBox::information(this,"登陆失败","未连接服务器，请检查配置或服务端状态");
            return;
        }

         char buf[8192]={0};


    LOGIN_REQ login_req={0};
    strcpy(login_req.phone,id.toUtf8());
    strcpy(login_req.password,encryptedPwd.toUtf8());
    strcpy(login_req.code,code.toUtf8());
    login_req.kind=kind;
    HEAD head={};
    head.service_type=LOGIN;
    head.data_len=sizeof(LOGIN_REQ);







    memcpy(buf,&head,sizeof(HEAD));
    memcpy(buf+sizeof(HEAD),&login_req,head.data_len);
    crcValidator.GenerateChecksum(buf,sizeof(HEAD)+sizeof(LOGIN_REQ));
    Socketmode::getInstance()->sendmsg(buf,sizeof(HEAD)+sizeof(LOGIN_REQ));
    qDebug()<<id<<endl;
    // 0老人->Old4护工->MainWidget1  5家属->Mainwidget（与 acceptthread status_code 一致）
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(loginsuccess(QString)),this,SLOT(login2(QString)), Qt::UniqueConnection);
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(loginsuccess1(QString)),this,SLOT(login1(QString)), Qt::UniqueConnection);
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(loginsuccess2(QString)),this,SLOT(login3(QString)), Qt::UniqueConnection);
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(nouser()),this,SLOT(usernoexit()), Qt::UniqueConnection);
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(passwordwarn()),this,SLOT(pwdwarn()), Qt::UniqueConnection);
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(passwordwarn()),this,SLOT(codewarn()), Qt::UniqueConnection);
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(loginRoleMismatch(QString)),this,SLOT(loginRoleMismatch(QString)), Qt::UniqueConnection);

    connect(Socketmode::getInstance(),SIGNAL(connectwarn()),this,SLOT(connectwarn()), Qt::UniqueConnection);
    }
}

void LoginWidget::codeget(QString code)
{
    this->ui->code_pushButton->setText(code);
}

// status_code 0：老人
void LoginWidget::login2(QString phone)
{
    this->hide();
    this->old->setuserid(phone);
    this->old->show();
}

// status_code 4：护工
void LoginWidget::login1(QString phone)
{
    this->hide();
    this->main1->setuserid(phone);
    this->main1->show();
}

// status_code 5：家属
void LoginWidget::login3(QString phone)
{
    this->hide();
    this->main->setuserid(phone);
    this->main->show();
    this->main->setupVideo();
}
void LoginWidget::usernoexit()
{
    QMessageBox::information(this,"登陆失败","  用户不存在");
}

void LoginWidget::pwdwarn()
{
    QMessageBox::information(this,"登陆失败","  密码错误");
}

void LoginWidget::codewarn()
{
    QMessageBox::information(this,"登陆失败","  验证码错误");
}

void LoginWidget::loginRoleMismatch(QString msg)
{
    if (msg.trimmed().isEmpty())
        msg = QStringLiteral("所选登录角色与账号注册身份不一致，请重新选择。");
    QMessageBox::information(this, QStringLiteral("登陆失败"), msg);
}

void LoginWidget::connectwarn()
{
    QMessageBox::information(this,"断开连接 ","  网络开小差了");
}

void LoginWidget::sendno()
{
       QMessageBox::information(this,"获取验证码失败","发送失败");
}

void LoginWidget::init_connect()
{
    connect(this->registers,SIGNAL(pwdtext(QString)),this,SLOT(turn(QString)));
    connect(this->registers,SIGNAL(backlogin()),this,SLOT(back()));
    connect(this->main, SIGNAL(logoutRequested()), this, SLOT(onChildLogout()), Qt::UniqueConnection);
    connect(this->main1, SIGNAL(logoutRequested()), this, SLOT(onChildLogout()), Qt::UniqueConnection);
    connect(this->old, SIGNAL(logoutRequested()), this, SLOT(onChildLogout()), Qt::UniqueConnection);
}

void LoginWidget::logincode()
{

    QString phone=this->ui->account_lineEdit->text().trimmed();
    if (phone.isEmpty()) {
        QMessageBox::information(this, "获取验证码失败", "请先输入账号");
        return;
    }
    if (!Socketmode::getInstance()->isConnected()) {
        QMessageBox::information(this, "获取验证码失败", "未连接到服务器，请先检查配置和服务端状态");
        return;
    }
    EncryptionDecryption ed;
    char encryptionKey = 0x55;

    char buf[8192]={0};
    CODE_REQ code_req={0};
    strcpy(code_req.phone,phone.toUtf8());
    code_req.type=1;

    HEAD head={};
    head.service_type=CODE;
    head.data_len=sizeof(CODE_REQ);
    head.client_fd=Socketmode::getInstance()->acceptthread->getfd();

    qDebug()<<"style is"<<head.service_type<<"len"<<head.data_len<<endl;

    memcpy(buf,&head,sizeof(HEAD));
    memcpy(buf+sizeof(HEAD),&code_req,head.data_len);
   crcValidator.GenerateChecksum(buf,sizeof(HEAD)+sizeof(CODE_REQ));
    Socketmode::getInstance()->sendmsg(buf,sizeof(HEAD)+sizeof(CODE_REQ));
    connect(Socketmode::getInstance()->acceptthread,SIGNAL(code(QString)),this,SLOT(codeget(QString)), Qt::UniqueConnection);

    connect(Socketmode::getInstance()->acceptthread,SIGNAL(sendwarn()),this,SLOT(sendno()), Qt::UniqueConnection);
}

void LoginWidget::on_code_pushButton_clicked()
{
    logincode();
}

QString LoginWidget::md5Encrypt(const QString &input)
{
     return QCryptographicHash::hash(input.toUtf8(), QCryptographicHash::Md5).toHex();
}

void LoginWidget::onChildLogout()
{
    this->main->hide();
    this->main1->hide();
    this->old->hide();
    this->ui->account_lineEdit->clear();
    this->ui->pwd_lineEdit->clear();
    this->ui->code_lineEdit->clear();
    this->show();
}
