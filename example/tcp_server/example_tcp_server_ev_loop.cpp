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

void ExampleServerEventLoop::onTimer(EventMessage *msg, void *data)
{
	LOG_INFO("total recv message count: %d", msg_cnt_);
	ServerEventLoop::onTimer(msg, data);
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
