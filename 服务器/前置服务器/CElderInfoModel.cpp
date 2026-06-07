#include "CElderInfoModel.h"
#include <cctype>

static void trimString(string& s)
{
	while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front())))
		s.erase(0, 1);
	while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back())))
		s.pop_back();
}

CElderInfoModel::CElderInfoModel()
{
}

CElderInfoModel::~CElderInfoModel()
{
}

bool CElderInfoModel::insertCElderInfo(ElderInfo elderinfo, string phone)
{
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();

        // 1. ???? SQL ??�䣬��Ӧ elder_info ������???
        string sql = "insert into elder_info(elder_id, user_id, name, age, gender, record_time, remark) "
            "values(?, (select user_id from user where user_phone= ? ), ?, ?, ?, ?, ?)";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setString(1, phone);
        pstmt->setString(2, phone);
        pstmt->setString(3, elderinfo.getName());
        pstmt->setInt(4, elderinfo.getAge());

        // 性别码统一支持 "1"/"2"（客户端发送），并兼容旧文本值
        int genderCode = 0;
        string gender = elderinfo.getGender();
        if (gender == "1" || gender == "男" || gender == "male" || gender == "M") {
            genderCode = 1;
        }
        else if (gender == "2" || gender == "女" || gender == "female" || gender == "F") {
            genderCode = 2;
        }
        pstmt->setInt(5, genderCode);

        pstmt->setString(6, elderinfo.getRecordTime());
        pstmt->setString(7, elderinfo.getRemark());

        // 3. ִ???��??
        pstmt->executeUpdate();

        // 4. �ͷ���Դ (ע�⣺???����� relesseDb ƴд??ʵ�� relesseDb�����ﲻ��Ҫ��)
        MysqlUtil::getInstance()->relesseDb(pstmt, NULL, conn);

        cout << elderinfo.getName() << ":���˻�����Ϣ����ɹ�" << endl;
        return true;
    }
    catch (sql::SQLException& e)
    {
        cout << "Error: " << e.what() << endl;
        cout << "Mysql error code: " << e.getErrorCode() << endl;
        cout << "SQL status: " << e.getSQLState() << endl;
        return false;
    }
}

bool CElderInfoModel::selectCElderInfoByPhone(const string& phone, ElderInfo& elderinfo)
{
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        string sql =
            "select ei.name, ei.age, ei.gender, ei.record_time, u.user_phone as contact, ei.remark "
            "from elder_info ei "
            "join user u on ei.user_id = u.user_id "
            "where ei.elder_id = ?";

        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setString(1, phone);
        ResultSet* rs = pstmt->executeQuery();

        bool found = false;
        if (rs->next())
        {
            elderinfo.setName(rs->getString("name"));
            elderinfo.setAge(rs->getInt("age"));
            int genderCode = rs->getInt("gender");
            elderinfo.setGender(to_string(genderCode));
            elderinfo.setRecordTime(rs->getString("record_time"));
            elderinfo.setContact(rs->getString("contact"));
            elderinfo.setRemark(rs->getString("remark"));
            found = true;
        }

        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
        return found;
    }
    catch (sql::SQLException& e)
    {
        cout << "Error: " << e.what() << endl;
        cout << "Mysql error code: " << e.getErrorCode() << endl;
        cout << "SQL status: " << e.getSQLState() << endl;
        return false;
    }
}

bool CElderInfoModel::syncFamilyElderBinding(const string& elderPhone, const string& contactPhone)
{
	string contact = contactPhone;
	trimString(contact);
	if (contact.empty())
		return true;
	string elder = elderPhone;
	trimString(elder);
	if (elder.empty() || contact == elder)
		return true;
	try {
		Connection* conn = MysqlUtil::getInstance()->getConnection();
		string qFamily =
			"SELECT user_id FROM user WHERE user_phone = ? AND identity_id = 0 LIMIT 1";
		PreparedStatement* ps1 = conn->prepareStatement(qFamily);
		ps1->setString(1, contact);
		ResultSet* rs1 = ps1->executeQuery();
		int familyUid = 0;
		if (rs1->next())
			familyUid = rs1->getInt("user_id");
		delete rs1;
		delete ps1;
		if (familyUid <= 0) {
			cout << "syncFamilyElderBinding: contact is not a registered family user, skip" << endl;
			conn->close();
			delete conn;
			return true;
		}
		string qElder = "SELECT user_id FROM user WHERE user_phone = ? LIMIT 1";
		PreparedStatement* ps2 = conn->prepareStatement(qElder);
		ps2->setString(1, elder);
		ResultSet* rs2 = ps2->executeQuery();
		int elderUid = 0;
		if (rs2->next())
			elderUid = rs2->getInt("user_id");
		delete rs2;
		delete ps2;
		if (elderUid <= 0) {
			conn->close();
			delete conn;
			return false;
		}
		string qIns =
			"INSERT IGNORE INTO family_elder (family_user_id, elder_user_id) VALUES (?, ?)";
		PreparedStatement* ps3 = conn->prepareStatement(qIns);
		ps3->setInt(1, familyUid);
		ps3->setInt(2, elderUid);
		ps3->executeUpdate();
		delete ps3;
		conn->close();
		delete conn;
		cout << "family_elder bind: family_user_id=" << familyUid << " elder_user_id=" << elderUid << endl;
		return true;
	}
	catch (sql::SQLException& e) {
		cout << "syncFamilyElderBinding error: " << e.what() << endl;
		return false;
	}
}
