
#include "CThreadPool.h"

CThreadPool::CThreadPool(const int thread_num)
{
	//初始化互斥量
	pthread_mutex_init(&this->mutex, NULL);
	//初始化条件变量
	pthread_cond_init(&this->conn, NULL);
	//按最小线程数创建线程，并添加至空闲列表中
	this->min_threadnum = thread_num;
	for (int i = 0; i < this->min_threadnum; i++)
	{
		pthread_t thread_id;
		pthread_create(&thread_id, NULL, thread_handle, this);
		//添加至空闲列表中
		this->idle_list.push_back(thread_id);
	}
}

CThreadPool::~CThreadPool()
{
}

bool CThreadPool::queueIsEmpty()
{
	return this->task_queue.empty();
}

void CThreadPool::lock()
{
	pthread_mutex_lock(&this->mutex);
}

void CThreadPool::unlock()
{
	pthread_mutex_unlock(&this->mutex);;
}

void CThreadPool::wait()
{
	pthread_cond_wait(&this->conn, &this->mutex);
}

void CThreadPool::notify()
{
	pthread_cond_signal(&this->conn);
}

void CThreadPool::pushTask(CBaseTask* task)
{
	this->lock();
	this->task_queue.push(task);
	this->unlock();
	//任务队列添加成功后，需唤醒一个线程去执行任务
	this->notify();
}

CBaseTask* CThreadPool::popTask()
{
	CBaseTask* ptask = this->task_queue.front();
	this->task_queue.pop();		//从任务队列中移除任务
	return ptask;
}
//从忙碌到空闲
void CThreadPool::moveToIdle(pthread_t id)
{
	list<pthread_t>::iterator it;
	//find就是由<algorithm>库提供
	it = find(busy_list.begin(), busy_list.end(), id);
	if (it != busy_list.end())
	{
		//从忙碌队列移除
		this->busy_list.erase(it);
		//加入到空闲队列
		this->idle_list.push_back(*it);
	}
}

void CThreadPool::moveToBusy(pthread_t id)
{
	list<pthread_t>::iterator it;
	it = find(idle_list.begin(), idle_list.end(), id);
	if (it != idle_list.end())
	{
		//从空闲队列移除
		this->idle_list.erase(it);
		//加入到忙碌队列
		this->busy_list.push_back(*it);
	}
}

//线程处理函数(静态方法，无this指针)
void* CThreadPool::thread_handle(void* pv)	//static属于类本质this不知指向谁
{
	//获取线程池对象
	CThreadPool* argThis = (CThreadPool*)pv;
	//获取当前线程的pthread_t(线程id)
	pthread_t thread_id = pthread_self();
	//确保主线程与当前线程的逻辑完全分离，当前执行线程结束后，id会被自动释放
	//分离目的：为了声明这个线程不会阻塞主线程的逻辑
	pthread_detach(thread_id);
	while (true)
	{
		argThis->lock();
		while (argThis->queueIsEmpty())
		{
			argThis->wait();
		}
		argThis->moveToBusy(thread_id);
		CBaseTask* task = argThis->popTask();
		argThis->unlock();
		//执行任务
		task->working();
		//将线程由忙碌队列移动到空闲队列
		argThis->lock();
		argThis->moveToIdle(thread_id);
		argThis->unlock();
	}
	return nullptr;
}