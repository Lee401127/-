#include "CHostAddress.h"

CHostAddress::CHostAddress(unsigned short port)
{
	this->port = port;
	this->addr.sin_family = AF_INET;	//设置协议簇IPV4
	this->addr.sin_addr.s_addr = INADDR_ANY;//让系统分配可用的IP地址作为服务器地址
	this->addr.sin_port = htons(port);
	this->length = sizeof(addr);
}

CHostAddress::~CHostAddress()
{
}

void CHostAddress::setPort(unsigned short port)
{
	this->port = port;
}

unsigned short CHostAddress::getPort()
{
	return this->port;
}

void CHostAddress::setAddress(sockaddr_in addr)
{
	this->addr = addr;
}


sockaddr* CHostAddress::getAddress()
{
	return (sockaddr*)&(this->addr);
}

int CHostAddress::getLength()
{
	return this->length;
}

