#include "CCallRecordModel.h"
#include "protecol.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

CCallRecordModel::CCallRecordModel() {}

CCallRecordModel::~CCallRecordModel() {}

bool CCallRecordModel::insertCall(const std::string& elder_phone, int call_type, const std::string& remark, int* out_call_id)
{
	if (out_call_id) *out_call_id = 0;
	try {
		Connection* conn = MysqlUtil::getInstance()->getConnection();
		string sql =
			"INSERT INTO call_record (elder_user_id, call_type, remark) "
			"VALUES ((SELECT user_id FROM user WHERE user_phone = ? LIMIT 1), ?, ?)";
		PreparedStatement* pstmt = conn->prepareStatement(sql);
			pstmt->setString(1, elder_phone);
		pstmt->setInt(2, call_type);
		pstmt->setString(3, remark);
		int n = pstmt->executeUpdate();
		if (n <= 0) {
			MysqlUtil::getInstance()->relesseDb(pstmt, NULL, conn);
			return false;
		}
		// LAST_INSERT_ID() 与本次 INSERT 必须在同一 Connection 上查询；
		// 若先 relesseDb 再 getConnection()，会得到新连接，LAST_INSERT_ID 恒为 0。
		delete pstmt;
		pstmt = conn->prepareStatement("SELECT LAST_INSERT_ID() AS id");
		ResultSet* rs = pstmt->executeQuery();
		int newId = 0;
		if (rs->next())
			newId = rs->getInt("id");
		MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
		if (out_call_id) *out_call_id = newId;
		return newId > 0;
	}
	catch (sql::SQLException& e) {
		cerr << "CCallRecordModel::insertCall: " << e.what() << endl;
		return false;
	}
}

bool CCallRecordModel::selectForRequester(const std::string& requester_phone, const std::string& elder_phone,
	int from, int to, std::vector<CallRecordEntity>& out)
{
	out.clear();
	int limit = to - from;
	if (from < 0 || limit <= 0 || limit > MAX_CALL_RECORD)
		return false;
	try {
		Connection* conn = MysqlUtil::getInstance()->getConnection();
		string qId = "SELECT identity_id FROM user WHERE user_phone = ? LIMIT 1";
		PreparedStatement* psId = conn->prepareStatement(qId);
		psId->setString(1, requester_phone);
		ResultSet* rsId = psId->executeQuery();
		int identity = -1;
		if (rsId->next())
			identity = rsId->getInt("identity_id");
		// 仅释放语句与结果集，必须保留 conn 供后续查询使用（relesseDb 会 delete conn）
		MysqlUtil::getInstance()->relesseDb(psId, rsId, nullptr);
		if (identity < 0) {
			MysqlUtil::getInstance()->relesseDb(nullptr, nullptr, conn);
			return false;
		}

		string sql;
		PreparedStatement* pstmt = nullptr;
		if (identity == 2) {
			// 护工：不按 family_elder 限制
			sql =
				"SELECT cr.call_id, u.user_phone, cr.call_type, "
				"DATE_FORMAT(cr.call_time, '%Y-%m-%d %H:%i:%s') AS ct, IFNULL(cr.remark,'') AS rm "
				"FROM call_record cr "
				"JOIN user u ON cr.elder_user_id = u.user_id "
				"WHERE cr.elder_user_id = (SELECT user_id FROM user WHERE user_phone = ? LIMIT 1) "
				"ORDER BY cr.call_time DESC "
				"LIMIT ? OFFSET ?";
			pstmt = conn->prepareStatement(sql);
			pstmt->setString(1, elder_phone);
			pstmt->setInt(2, limit);
			pstmt->setInt(3, from);
		}
		else if (identity == 0) {
			// 家属：必须在 family_elder 中与该老人绑定
			sql =
				"SELECT cr.call_id, u.user_phone, cr.call_type, "
				"DATE_FORMAT(cr.call_time, '%Y-%m-%d %H:%i:%s') AS ct, IFNULL(cr.remark,'') AS rm "
				"FROM call_record cr "
				"JOIN user u ON cr.elder_user_id = u.user_id "
				"WHERE cr.elder_user_id = (SELECT user_id FROM user WHERE user_phone = ? LIMIT 1) "
				"AND EXISTS ( "
				"  SELECT 1 FROM family_elder fe "
				"  WHERE fe.elder_user_id = cr.elder_user_id "
				"  AND fe.family_user_id = (SELECT user_id FROM user WHERE user_phone = ? LIMIT 1) "
				") "
				"ORDER BY cr.call_time DESC "
				"LIMIT ? OFFSET ?";
			pstmt = conn->prepareStatement(sql);
			pstmt->setString(1, elder_phone);
			pstmt->setString(2, requester_phone);
			pstmt->setInt(3, limit);
			pstmt->setInt(4, from);
		}
		else {
			MysqlUtil::getInstance()->relesseDb(nullptr, nullptr, conn);
			return false;
		}

		ResultSet* rs = pstmt->executeQuery();
		while (rs->next()) {
			CallRecordEntity row;
			row.call_id = rs->getInt("call_id");
			row.elder_phone = rs->getString("user_phone");
			row.call_type = rs->getInt("call_type");
			row.call_time = rs->getString("ct");
			row.remark = rs->getString("rm");
			out.push_back(row);
		}
		MysqlUtil::getInstance()->relesseDb(pstmt, rs, conn);
		return true;
	}
	catch (sql::SQLException& e) {
		cerr << "CCallRecordModel::selectForRequester: " << e.what() << endl;
		return false;
	}
}
