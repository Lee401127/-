#pragma once
#include <netinet/in.h>
class CHostAddress
{
private:
	unsigned short port;
	struct sockaddr_in addr;
	int length;
public:
	//¹¹Ôì
	CHostAddress(unsigned short port);
	//Îö¹¹
	~CHostAddress();
	void setPort(unsigned short port);
	unsigned short getPort();
	void setAddress(struct sockaddr_in addr);
	struct sockaddr* getAddress();
	int getLength();
};

