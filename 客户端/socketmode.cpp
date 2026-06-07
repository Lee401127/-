#include "socketmode.h"
#include<QDebug>
#include<QCoreApplication>
Socketmode *Socketmode::socketmode=nullptr;
Socketmode *Socketmode::getInstance()
{
    if(Socketmode::socketmode==nullptr)
       {
           Socketmode::socketmode=new Socketmode;

       }
    return Socketmode::socketmode;
}

Socketmode::Socketmode()
{
    this->socketfd = -1;
    this->acceptthread = nullptr;
    QDir appDir(QCoreApplication::applicationDirPath());
    QString configDirPath = appDir.filePath("settingfile");
    QString configPath = QDir(configDirPath).filePath("parking_system.conf");
    if(readConfig(configPath.toStdString())==true)
    {
        socketfd = socket(AF_INET, SOCK_STREAM, 0);//安装socket1.IPV4协议2.流式传输http/数据包UDP
    if (socketfd < 0)
    {
        perror("scoket error");
        return ;
    }
    qDebug()<< "scoketfd " << socketfd << endl;
    //连接服务器
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;//使用IPV4协议
    //服务器端的地址
    //127.0.0.1回环地址，通常用于做本地网络测试使用
    addr.sin_addr.s_addr = inet_addr(this->server_ip.c_str());
    addr.sin_port = htons(this->server_port);
    int res = ::connect(socketfd, (struct sockaddr*)&addr, sizeof(addr));
    if (res < 0)
    {
        perror("connect error");
        emit connectwarn();
        ::close(socketfd);
        socketfd = -1;

        return ;
    }
    qDebug() << "connect success" << endl;
        this->acceptthread = new AcceptThread(this->socketfd);
        this->acceptthread->start();
    } else {
        qDebug() << "skip socket init: config file missing or invalid";
    }
}

int Socketmode::sendmsg(char *msg, int len)
{
    if (this->socketfd < 0 || this->acceptthread == nullptr) {
        emit connectwarn();
        return -1;
    }
     int res=write(this->socketfd,msg,len);
    // qDebug()<<"length="<<len<<endl;
     return res;
}

bool Socketmode::readConfig(const string &path)
{
    std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "无法打开配置文件: " << path << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            // 移除注释部分
            size_t commentPos = line.find('#');
            if (commentPos != std::string::npos) {
                line = line.substr(0, commentPos);
            }

            // 跳过空行
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            if (line.empty()) continue;

            // 解析键值对
            size_t delimiterPos = line.find('=');
            if (delimiterPos == std::string::npos) continue;

            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            // 分配配置值
            if (key == "server_ip") {
                this->server_ip = value;
            } else if (key == "server_port") {
                try {
                    this->server_port = std::stoi(value);
                } catch (...) {
                    std::cerr << "无效端口号: " << value << std::endl;
                }
            } else if (key == "image_save_path") {
                this->image_path = value;
            } else if (key == "video_save_path") {
                this->video_path = value;
            } else if (key == "storage_size") {
                try {
                    this->storage_size = std::stoi(value);
                } catch (...) {
                    std::cerr << "无效存储容量: " << value << std::endl;
                }
            }
        }

        file.close();
        return true;
}

void Socketmode::socketconnect(string server_ip, int server_port)
{


        socketfd = socket(AF_INET, SOCK_STREAM, 0);//安装socket1.IPV4协议2.流式传输http/数据包UDP
    if (socketfd < 0)
    {
        perror("scoket error");
        return ;
    }
    qDebug()<< "scoketfd " << socketfd << endl;
    //连接服务器
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;//使用IPV4协议
    //服务器端的地址
    //127.0.0.1回环地址，通常用于做本地网络测试使用
    addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
    addr.sin_port = htons(server_port);
    int res = ::connect(socketfd, (struct sockaddr*)&addr, sizeof(addr));
    if (res < 0)
    {
        perror("connect error");
        emit connectwarn();

        return ;
    }
    qDebug() << "connect success" << endl;

    this->acceptthread=nullptr;
    this->acceptthread=new AcceptThread(this->socketfd);

    this->acceptthread->start();
}

bool Socketmode::isConnected() const
{
    return this->socketfd >= 0 && this->acceptthread != nullptr;
}


