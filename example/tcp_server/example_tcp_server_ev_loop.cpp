#include "example_tcp_server_ev_loop.h"

ExampleServerEventLoop::ExampleServerEventLoop(int max_msg_type, int capacity, int flags)
	: ServerEventLoop(max_msg_type, capacity, flags)
	, msg_cnt_(0)
{}
ExampleServerEventLoop::~ExampleServerEventLoop()
{}

void ExampleServerEventLoop::registerCallbacks()
{
	ServerEventLoop::registerCallbacks();
	BABELTRADER_EV_CB(EXAMPLE_MSG_FOO, onMessageFoo, MessageFoo);
}

void ExampleServerEventLoop::onTimer(EventMessage *, void *)
{
	LOG_INFO("total recv message count: %d", msg_cnt_);

	// close idle connection
	uint64_t curr_ts = (uint64_t)time(nullptr);
	for (TCPSession *session : tcp_sessions_)
	{
		if (curr_ts - session->last_active > 15)
		{
			LOG_WARNING(
				"close idle connection: "
				"remote_addr=%s, curr_ts=%llu, last_active=%llu",
				session->remote_addr,
				(unsigned long long)curr_ts,
				(unsigned long long)session->last_active);
			session->peer->close();
		}
	}
}
void ExampleServerEventLoop::onMessageFoo(EventMessage *msg, MessageFoo *data)
{
	TCPSession *session = (TCPSession*)msg->session;
	LOG_INFO("on message foo: remote_addr=%s, i64=%lld, s=%s",
		session->remote_addr, (long long)data->i64, data->s);
	msg_cnt_++;

	NetMessageBar bar;
	BABELTRADER_FILLUP_NET_HEAD(bar, EXAMPLE_MSG_BAR);
	bar.msg.f = float(data->i64);
	bar.msg.d = -1.0 * double(data->i64);
	strncpy(bar.msg.s, data->s, sizeof(bar.msg.s) - 1);

	TCPSocketHandle *handle = (TCPSocketHandle*)session->handle;
	handle->send((NetworkSession*)session, &bar, sizeof(bar));
}
