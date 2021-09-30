#include "session_manager.h"

NS_BABELTRADER_BEGIN

union u_session_id
{
	uint64_t session_id;
	struct
	{
		uint64_t datetime:40;
		uint64_t increase:24;
	};
};

SessionManager::SessionManager()
	: increase_id_(0)
{}

SessionManager::~SessionManager()
{}

uint64_t SessionManager::newSessionId()
{
	u_session_id session_id;

	uint64_t increase = ++increase_id_;
	session_id.increase = IDX_IN_POW_OF_2_RING(increase, (1<<23));

	time_t ts = time(NULL);
	struct tm t;
	gmtime_r(&ts, &t);
	session_id.datetime
		= ((t.tm_year + 1900) % 100) * 10000000000
		+ (t.tm_mon + 1) * 100000000
		+ (t.tm_mday) * 1000000
		+ (t.tm_hour) * 10000
		+ (t.tm_min) * 100
		+ t.tm_sec;

	return session_id.session_id;
}

NS_BABELTRADER_END
