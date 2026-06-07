#include "CTcpServer.h"

CTcpServer::CTcpServer(unsigned short port)
{
	this->address = new CHostAddress(port);
	this->socketfd = 0;
}

CTcpServer::~CTcpServer()
{
}

CHostAddress* CTcpServer::getAddress()
{
	return this->address;
}

int CTcpServer::getScoketfd()
{
	return this->socketfd;
}

//启动服务器
void CTcpServer::start()
{
	//1、创建Socket,返回socket的文件描述符
	this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketfd < 0)
	{
		perror("socket error");
		return;
	}
	cout << "socketfd is" << this->socketfd << endl;
	//2、绑定端口 bind
	int res = bind(this->socketfd, this->address->getAddress(), this->address->getLength());	//绑定端口
	if (res == -1)
	{
		perror("bind error");
		return;
	}
	cout << "已绑定" << this->address->getPort() << "端口" << endl;
	//3、开启服务器监听
	res = listen(this->socketfd, 10);//10表示最大支持10个连接
	if (res == -1)
	{
		perror("listen error");
		return;
	}
	cout << "服务器初始化完成" << endl;
}

void CTcpServer::stop()
{
	close(socketfd);
	this->socketfd = 0;
}
