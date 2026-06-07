#pragma once
#include "CHostAddress.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <map>
#include <string.h>
#include "protecol.h"
using namespace std;
class CTcpServer
{
private:
	CHostAddress* address;
	int socketfd;
public:
	CTcpServer(unsigned short port);
	~CTcpServer();
	CHostAddress* getAddress();
	int getScoketfd();
	void start();	//启动服务器(服务器初始化)
	//void run();		//运行服务器
	void stop();	//停止服务器
};

