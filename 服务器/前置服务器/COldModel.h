#include "MysqlUtil.h"
#include<list>
#include"protecol.h"
#include "Cold.h"
#include <cstring>
#include <iostream>
using namespace std;
class COldModel
{
private:



public:
	COldModel();
	~COldModel();
	//通过号码查询角色	

	//增加用户
	bool insertUser(Cold u);
	vector<Eld> getOldList(int from, int to);
	vector<Eld> getOldListForFamily(int from, int to, const string& family_phone);

};

