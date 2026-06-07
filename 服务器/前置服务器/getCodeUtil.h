#pragma once
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <openssl/sha.h>
#include<iostream>
using namespace std;
#define MAXLINE 4096
#define MAXPARAM 2048
#define LISTENQ 1024
extern int h_errno;



/* 安全释放资源宏 */
#define SAFE_CLOSE(fd) do { if(fd >= 0) { close(fd); fd = -1; } } while(0)
class getCodeUtil
{
public:
    getCodeUtil(char* mobile);
    ~getCodeUtil();
    int safe_connect(const char* host, const char* service);
    ssize_t http_post(const char* page, const char* poststr);
    int send_sms();

    char* getCode();
    bool isSend();

private:
    char* mobile;
    char* mycode;


};

