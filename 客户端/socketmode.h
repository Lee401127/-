#ifndef SOCKETMODE_H
#define SOCKETMODE_H
#include <QObject>
#include<QString>
#include<QDebug>
#include"protecol.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include <string>
#include<QFileDialog>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include<QMessageBox>
#include"acceptthread.h"
#include<QMessageBox>
#include<QList>
#include"settingfile.h"
using namespace std;

class Socketmode: public QObject
{
    Q_OBJECT

public:
    static Socketmode *getInstance();
    Socketmode();
    int socketfd; // 改为成员变量
    int sendmsg(char*msg,int len);
     AcceptThread *acceptthread;
    bool readConfig(const std::string& path);
    void socketconnect(string server_ip,
    int server_port );
    bool isConnected() const;

private:
    static Socketmode* socketmode;
    string server_ip;
    int server_port ;
    string image_path ;
    string video_path ;
    int storage_size;  // GB

signals:
    void connectwarn();
};

#endif // SOCKETMODE_H
