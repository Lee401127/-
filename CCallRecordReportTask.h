#pragma once
#include "CBaseTask.h"
#include "shmWrite.h"

class CCallRecordReportTask : public CBaseTask {
	shmWrite* p;
public:
	CCallRecordReportTask(char* data, shmWrite* p);
	virtual ~CCallRecordReportTask();
	virtual void working();
};
