#include "example_tcp_server_ev_loop.h"

ExampleServerEventLoop::ExampleServerEventLoop(int max_msg_type, int capacity, int flags)
	: ServerEventLoop(max_msg_type, capacity, flags)
{}
ExampleServerEventLoop::~ExampleServerEventLoop()
{}

void ExampleServerEventLoop::registerCallbacks()
{
	ServerEventLoop::registerCallbacks();
	BABELTRADER_EV_CB(EXAMPLE_MSG_FOO, onMessageFoo, MessageFoo);
	BABELTRADER_EV_CB(EXAMPLE_MSG_BAR, onMessageBar, MessageBar);
}

void ExampleServerEventLoop::onTimer(EventMessage *, void *)
{
	LOG_INFO("on timer......");
}
void ExampleServerEventLoop::onMessageFoo(EventMessage *msg, MessageFoo *data)
{
	TCPSession *session = (TCPSession*)msg->session;
	LOG_INFO("on message foo: remote_addr=%s, i64=%lld, s=%s",
		session->remote_addr, (long long)data->i64, data->s);
}
void ExampleServerEventLoop::onMessageBar(EventMessage *msg, MessageBar *data)
{
	TCPSession *session = (TCPSession*)msg->session;
	LOG_INFO("on message bar: remote_addr=%s, s=%s, f=%f, d=%f",
		session->remote_addr, data->s, data->f, data->d);
}
