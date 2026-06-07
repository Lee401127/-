#pragma once
#include "MysqlUtil.h"
#include <string>
#include <vector>

struct CallRecordEntity {
	int call_id;
	std::string elder_phone;
	int call_type;
	std::string call_time;
	std::string remark;
};

class CCallRecordModel {
public:
	CCallRecordModel();
	~CCallRecordModel();
	bool insertCall(const std::string& elder_phone, int call_type, const std::string& remark, int* out_call_id);
	/** requester_phone：当前登录者手机号；家属(identity0) 需 family_elder 绑定，护工(identity 2) 可查任意老人通话 */
	bool selectForRequester(const std::string& requester_phone, const std::string& elder_phone,
		int from, int to, std::vector<CallRecordEntity>& out);
};
