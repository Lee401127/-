#ifndef SETTING_H
#define SETTING_H
#include <string>
#include <QWidget>
#include<QFileDialog>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include<QMessageBox>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
//#include<socketmode.h>
using namespace std;
namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();
    void init_connect();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();



signals:
    void finish();
private:
    Ui::Setting *ui;
    QString configPath; // 动态生成的配置文件路径
    bool validateInput();            // 输入验证
    bool validateIP(const QString& ip);   // IP地址验证
    bool validatePort(const QString& port); // 端口验证
};

#endif // SETTING_H
