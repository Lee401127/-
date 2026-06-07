#include "register.h"
#include "ui_register.h"
#include <Qt>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->isclicked=false;
}

Register::~Register()
{
    delete ui;
}

void Register::passpwd(QString pwd)
{
    this->ui->pwd_lineEdit->setText(pwd);
    emit pwdtext(pwd);
}

void Register::codeget(QString code)
{
    this->ui->code_pushButton->setText(code);
}

void Register::registerno()
{
    QMessageBox::information(this,"注册失败","验证码错误");
}

void Register::phonebeenused()
{
    QMessageBox::information(this,"获取验证码失败","手机号已被使用");
    this->isclicked=false;
}

void Register::sendno()
{
    QMessageBox::information(this,"获取验证码失败","发送失败");
    this->isclicked=false;
}

void Register::on_pushButton_clicked()
{
    QString phone=this->ui->phone_Edit->text().trimmed();
    QString code=this->ui->code_lineEdit->text().trimmed();
    int currentIndex = this->ui->comboBox->currentIndex();
    if (currentIndex == 0) {
        kind = 0;
    } else if (currentIndex == 1) {
        kind = 1;
    } else if (currentIndex == 2) {
        kind = 2;
    }
    if(phone.isEmpty()||code.isEmpty())
    {
        QMessageBox::information(this,"注册失败","手机号验证码不能为空");
         return;
    }
    else
    {

         char buf[8192]={0};
         REGISTER_REQ register_req={0};
         strcpy(register_req.phone,phone.toUtf8());
         strcpy(register_req.code,code.toUtf8());
         register_req.kind=kind;
         HEAD head={};
         head.service_type=REGISTER;
         head.data_len=sizeof (REGISTER_REQ);


         memcpy(buf,&head,sizeof(HEAD));
         memcpy(buf+sizeof(HEAD),&register_req,head.data_len);
         crcValidator.GenerateChecksum(buf,sizeof(HEAD)+sizeof(REGISTER_REQ));
         Socketmode::getInstance()->sendmsg(buf,sizeof(HEAD)+sizeof(REGISTER_REQ));
         connect(Socketmode::getInstance()->acceptthread,SIGNAL(password(QString)),this,SLOT(passpwd(QString)), Qt::UniqueConnection);
         connect(Socketmode::getInstance()->acceptthread,SIGNAL(registerswarn()),this,SLOT(registerno()), Qt::UniqueConnection);



    }
}

void Register::on_cancle_pushButton_clicked()
{
    emit backlogin();
}

void Register::on_code_pushButton_clicked()
{
    QString phone=this->ui->phone_Edit->text().trimmed();
    if(this->isclicked==false)
    {
    if(phone.isEmpty())
    {
        QMessageBox::information(this,"验证码获取失败","手机号验证码不能为空");
         return;
    }
    else
    {
         char buf[8192]={0};
         CODE_REQ code_req={0};
         strcpy(code_req.phone,phone.toUtf8());
         code_req.type=0;

         HEAD head={};
         head.service_type=CODE;
         head.data_len=sizeof(CODE_REQ);


         memcpy(buf,&head,sizeof(HEAD));
         memcpy(buf+sizeof(HEAD),&code_req,head.data_len);

         crcValidator.GenerateChecksum(buf,sizeof(HEAD)+sizeof(CODE_REQ));
         Socketmode::getInstance()->sendmsg(buf,sizeof(HEAD)+sizeof(CODE_REQ));
         connect(Socketmode::getInstance()->acceptthread,SIGNAL(code(QString)),this,SLOT(codeget(QString)), Qt::UniqueConnection);
         connect(Socketmode::getInstance()->acceptthread,SIGNAL(phonehasbeenused()),this,SLOT(phonebeenused()), Qt::UniqueConnection);
         connect(Socketmode::getInstance()->acceptthread,SIGNAL(sendwarn()),this,SLOT(sendno()), Qt::UniqueConnection);
    }
    this->isclicked=true;
    }else {

}
}
