
#pragma once
#include <iostream>
#include <map>
#include <string.h>
#include "shmWrite.h"
#include "ModelFactory.h"
using namespace std;
class CBaseTask
{
public:
	static pthread_mutex_t mutex;
	CBaseTask(char* data);
	virtual ~CBaseTask();	//ĞéÎö¹¹
	virtual void working() = 0;
	char data[8192];	//»º³åÇø

};

