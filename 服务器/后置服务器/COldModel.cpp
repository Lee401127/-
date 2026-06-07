#include "COldModel.h"

COldModel::COldModel()
{
}

COldModel::~COldModel()
{
}

bool COldModel::insertUser(Cold u)
{
    try
    {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        // 移除 elder_id 列，让数据库自动生成
        string sql = "insert into elder (user_phone) values(?)";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setString(1, u.getUserphone());   // 只设置 user_id

        int res = pstmt->executeUpdate();
        MysqlUtil::getInstance()->relesseDb(pstmt, NULL, conn);
        return true;
    }
    catch (sql::SQLException& e)
    {
        cout << "Error" << e.what() << endl;
        cout << "Mysql error code:" << e.getErrorCode() << endl;
        cout << "SQL status:" << e.getSQLState() << endl;
        return false;
    }
}

vector<Eld> COldModel::getOldList(int from, int to)
{
    vector<Eld> oldList;
    if (from < 0 || to <= from) {
        cerr << "Invalid range: from=" << from << ", to=" << to << endl;
        return oldList;  // ���ؿ��б�
    }

    int count = to - from;
    // ��ѡ�����������������ֹ�ڴ����
    if (count > MAX_OLD) {
        cerr << "Requested count exceeds MAX_OLD, truncating to " << MAX_OLD << endl;
        count = MAX_OLD;
    }

    try {
        Connection* conn = MysqlUtil::getInstance()->getConnection();
        // ֻ���� elder_info ���ѽ��������ˣ�������� activity/medicine/blood ���ʧ��
        // oldnum ����ʹ�� user_id��int���������ڿͻ����б���������ʾ��������
        // identity_id=1 Ϊ�����˺ţ�����ע�ᡢ��δ���� elder_info �ģ�
        string sql = "SELECT u.user_id AS elder_id, u.user_phone "
                     "FROM user u "
                     "WHERE u.identity_id = 1 "
                     "ORDER BY u.user_id "
                     "LIMIT ? OFFSET ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setInt(1, count);   // ����
        pstmt->setInt(2, from);    // ƫ����

        ResultSet* rs = pstmt->executeQuery();
        while (rs->next()) {
            Eld old;
            old.oldnum = rs->getInt("elder_id");
            string phone = rs->getString("user_phone");
            // ȷ�� phone ������ 11 ���ַ����� '\0' �� 12��
            strncpy(old.phone, phone.c_str(), sizeof(old.phone) - 1);
            old.phone[sizeof(old.phone) - 1] = '\0';
            oldList.push_back(old);
        }

        // �ͷ���Դ���ڷ���ǰ��ɣ�
        MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
    }
    catch (sql::SQLException& e) {
        cerr << "SQL error in getOldList: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << endl;
        // �����쳣ʱ���ؿ� vector
        return vector<Eld>();
    }

	return oldList;
}

vector<Eld> COldModel::getOldListForFamily(int from, int to, const string& family_phone)
{
	vector<Eld> oldList;
	if (from < 0 || to <= from) {
		cerr << "getOldListForFamily invalid range" << endl;
		return oldList;
	}
	int count = to - from;
	if (count > MAX_OLD) {
		count = MAX_OLD;
	}
	if (family_phone.empty()) {
		return oldList;
	}
	try {
		Connection* conn = MysqlUtil::getInstance()->getConnection();
		string sql =
			"SELECT u.user_id AS elder_id, u.user_phone "
			"FROM family_elder fe "
			"JOIN user u ON fe.elder_user_id = u.user_id "
			"JOIN elder_info ei ON ei.user_id = u.user_id "
			"WHERE fe.family_user_id = (SELECT user_id FROM user WHERE user_phone = ? LIMIT 1) "
			"LIMIT ? OFFSET ?";
		PreparedStatement* pstmt = conn->prepareStatement(sql);
		pstmt->setString(1, family_phone);
		pstmt->setInt(2, count);
		pstmt->setInt(3, from);
		ResultSet* rs = pstmt->executeQuery();
		while (rs->next()) {
			Eld old;
			old.oldnum = rs->getInt("elder_id");
			string phone = rs->getString("user_phone");
			strncpy(old.phone, phone.c_str(), sizeof(old.phone) - 1);
			old.phone[sizeof(old.phone) - 1] = '\0';
			oldList.push_back(old);
		}
		MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
	}
	catch (sql::SQLException& e) {
		cerr << "getOldListForFamily SQL error: " << e.what() << endl;
		return vector<Eld>();
	}
	return oldList;
}

