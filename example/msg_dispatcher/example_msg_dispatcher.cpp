#include "babeltrader/base/babeltrader_base.h"

enum
{
	MSG_NULL,
	MSG_FOO,
	MSG_BAR,
	MAX_MESSAGE_ID,
};

struct MessageFoo
{
	int64_t  foo_i64;
	int32_t  foo_i32;
	uint32_t foo_u32;
};

struct MessageBar
{
	char s[32];
};

void FooCallback(MessageFoo *msg)
{
	LOG_INFO("callback - foo message: i64=%lld, i32=%ld, u32=%lu",
		(long long)msg->foo_i64, (long)msg->foo_i32, (unsigned long)msg->foo_u32);
}

class BarCallback
{
public:
	void func(MessageBar *msg)
	{
		LOG_INFO("callback - bar message: s=%s", msg->s);
	}
};

int main()
{
	// initialize log, console only
	babeltrader::Log::Init(LOG_LEVEL_INFO, NULL, 0);

	BarCallback bar_cb;

	// register callbacks
	babeltrader::MessageDispatcher dispatcher(MAX_MESSAGE_ID);
	dispatcher.Register<MessageFoo>(MSG_FOO, std::bind(FooCallback, std::placeholders::_1));
	dispatcher.Register<MessageBar>(MSG_BAR, std::bind(&BarCallback::func, &bar_cb, std::placeholders::_1));

	// invoke dispatcher
	{
		MessageFoo msg;
		memset(&msg, 0, sizeof(msg));
		msg.foo_i64 = 1;
		msg.foo_i32 = 2;
		msg.foo_u32 = 3;
		dispatcher.OnMessage(MSG_FOO, &msg);
	}

	{
		MessageBar msg;
		memset(&msg, 0, sizeof(msg));
		strncpy(msg.s, "bar", sizeof(msg.s)-1);
		dispatcher.OnMessage(MSG_BAR, &msg);
	}

	return 0;
}
