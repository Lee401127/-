#pragma once
#include <sys/epoll.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include "CTcpServer.h"
#include "shmWrite.h"
#include "shmRead.h"
#include "CRCUtil.h"
#define BLOCKNUM 50

using namespace std;


class CEpollServer
{
private:
	CTcpServer* tcpserver;
	shmWrite* shmW1;
	shmRead* shmR1;

public:
	CEpollServer(unsigned short port);
	~CEpollServer();
	void EpollStart();
	void readData(int clienfd, struct epoll_event epollEvent, int epollfd);
	CRCUtil crcutil;
protected:

};

