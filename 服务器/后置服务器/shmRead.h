#pragma once
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <string.h>
#include "protecol.h"
#define BLOCKNUM 50

using namespace std;

class shmRead
{
public:
	shmRead(key_t shmkey, key_t msgkey, key_t semkey);

	int sem_create(key_t key, int sem_num);    //创建信号量
	int sem_p(int semid, int semindex);    //信号量的P操作
	int sem_v(int semid, int semindex);    //信号量的V操作


	void read_shm(char* data);

	void* shmaddr;    //共享内存首地址
	int shmid;    //共享内存id
	int msgid;    //消息队列id
	int semid;    //信号量id
	MSGBUF recvbuf;        //消息队列发送消息
	int arr[BLOCKNUM];
	int index;        //数组当前下标
	char buf[8192];    //一块数据区保存内容
};

