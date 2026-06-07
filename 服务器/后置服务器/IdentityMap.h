#pragma once

/**
 * 客户端协议 LOGIN_REQ / REGISTER_REQ 的 kind：0 老人，1 护工，2 家属。
 * 数据库 user.identity_id：1 老人，2 护工，0 家属。
 */
inline int protocolKindToDbIdentity(int kind)
{
	switch (kind) {
	case 0: return 1;
	case 1: return 2;
	case 2: return 0;
	default: return -1;
	}
}
