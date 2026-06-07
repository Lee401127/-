

#include "CBaseTask.h"


pthread_mutex_t CBaseTask::mutex;
CBaseTask::CBaseTask(char* data)
{
	pthread_mutex_init(&mutex, NULL);
	bzero(this->data, sizeof(this->data));
	memcpy(this->data, data, sizeof(this->data));

}
CBaseTask::~CBaseTask()
{
	pthread_mutex_destroy(&mutex);
}