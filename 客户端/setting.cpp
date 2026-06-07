#include "setting.h"
#include "ui_setting.h"

// IPv4正则表达式验证器
const QRegExp ipRegex("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
                     "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    QDir appDir(QCoreApplication::applicationDirPath());
      QString configDirPath = appDir.filePath("settingfile");
      configPath = QDir(configDirPath).filePath("parking_system.conf");
    ui->setupUi(this);
    // 设置IP输入验证
        QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
        ui->ip_lineEdit->setValidator(ipValidator);

        // 设置端口输入验证（1-65535）
        ui->lineEdit_5->setValidator(new QIntValidator(1, 65535, this));

}

Setting::~Setting()
{
    delete ui;
}



bool Setting::validateInput()
{
    // 检查必填项
       if(ui->ip_lineEdit->text().isEmpty() ||
          ui->lineEdit_5->text().isEmpty() ||
          ui->plant_lineEdit->text().isEmpty() ||
          ui->video_lineEdit->text().isEmpty() ||
          ui->save_lineEdit->text().isEmpty()) {
           return false;
       }

       // IP地址格式验证
       if(!validateIP(ui->ip_lineEdit->text().trimmed())) {
           return false;
       }

       // 端口号验证
       if(!validatePort(ui->lineEdit_5->text().trimmed())) {
           return false;
       }

       return true;
}

bool Setting::validateIP(const QString &ip)
{
    return ipRegex.exactMatch(ip);
}

bool Setting::validatePort(const QString &port)
{
    bool ok;
       int portNum = port.toInt(&ok);
       return ok && portNum > 0 && portNum <= 65535;
}

void Setting::on_pushButton_3_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this);
    ui->plant_lineEdit->setText(folderPath);
}

void Setting::on_pushButton_4_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this);
    ui->video_lineEdit->setText(folderPath);
}






void Setting::on_pushButton_clicked()
{
    if(!validateInput()) {
           QMessageBox::critical(this, "输入错误", "请检查以下问题：\n"
                                 "- IP地址格式无效\n"
                                 "- 端口号超出范围(1-65535)\n"
                                 "- 必填项未填写");
           return;
       }

       // 获取参数（经过验证的输入）
       std::string server_ip = ui->ip_lineEdit->text().trimmed().toStdString();
       int server_port = ui->lineEdit_5->text().toInt();
       std::string image_path = ui->plant_lineEdit->text().trimmed().toStdString();
       std::string video_path = ui->video_lineEdit->text().trimmed().toStdString();
       int storage_size = ui->save_lineEdit->text().trimmed().toInt();

    // 创建配置目录（如果不存在）
       QDir configDir = QFileInfo(configPath).absoluteDir();
           if (!configDir.exists()) {
               bool dirCreated = configDir.mkpath("."); // 递归创建目录
               if (!dirCreated) {
                   QMessageBox::critical(this, "错误", "无法创建配置目录: " + configDir.absolutePath());
                   return;
               }
           }

           // 打开配置文件
              std::ofstream config_file(configPath.toStdString());
              if (!config_file.is_open()) {
                  QMessageBox::critical(this, "错误", "无法打开配置文件: " + configPath);
                  return;
              }

        // 写入配置项
        config_file << "# 智慧停车系统配置文件\n\n";
        config_file << "server_ip=" << server_ip << "\n";
        config_file << "server_port=" << server_port << "\n";
        config_file << "image_save_path=" << image_path << "\n";
        config_file << "video_save_path=" << video_path << "\n";
        config_file << "storage_size=" << storage_size << "  # 单位：GB\n";

        config_file.close();
        std::cout << "配置文件已更新: " << configPath.toStdString() << std::endl;

        //   Socketmode::getInstance()->socketconnect(server_ip,server_port);

           QMessageBox::information(this, "成功", "配置已更新");
           emit finish();
}

