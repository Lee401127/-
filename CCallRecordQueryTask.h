#pragma once
#include "CBaseTask.h"
#include "shmWrite.h"

class CCallRecordQueryTask : public CBaseTask {
	shmWrite* p;
public:
	CCallRecordQueryTask(char* data, shmWrite* p);
	virtual ~CCallRecordQueryTask();
	virtual void working();
};
