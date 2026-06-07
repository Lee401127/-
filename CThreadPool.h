
#pragma once
#define MIN_NUM 10	//最小线程数(默认值)
#include <pthread.h>
#include <iostream>
#include "CBaseTask.h"
#include <queue>
#include <list>
#include <algorithm>	//包含了许多常用的算法函数,提供了容器操作的相关功能
using namespace std;
class CThreadPool
{
public:
	CThreadPool(const int thread_num = MIN_NUM);
	~CThreadPool();
	bool queueIsEmpty();	//判断当前任务队列是否为空
	void lock();	//加锁
	void unlock();	//解锁
	void wait();	//等待(控制线程进入等待状态，释放CPU资源给其他线程)
	void notify();	//唤醒(通知，唤醒任意一个等待中的线程)
	static void* thread_handle(void* pv);	//线程处理函数
	void pushTask(CBaseTask* task);			//添加新任务到任务队列
	CBaseTask* popTask();					//从任务队列中移除一个任务
	void moveToIdle(pthread_t id);			//移动任务线程到空闲列表
	void moveToBusy(pthread_t id);			//移动任务线程到忙碌列表
private:
	int min_threadnum;	//最小线程数
	int max_threadnum;	//最大线程数
	queue<CBaseTask*> task_queue;	//任务队列
	list<pthread_t> busy_list;	//忙碌列表(存放忙碌线程)
	list<pthread_t> idle_list; //空闲列表(存放空闲线程)
	pthread_mutex_t mutex;	//互斥锁,解决线程安全问题
	pthread_cond_t conn;	//线程条件变量，作用：让线程可以阻塞等待和唤醒


};
