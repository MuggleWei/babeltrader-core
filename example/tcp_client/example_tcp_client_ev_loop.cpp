#include "example_tcp_client_ev_loop.h"

#define STOP_REQ_ID 1000

ExampleClientEventLoop::ExampleClientEventLoop(int max_msg_type, int capacity, int flags)
	: ServerEventLoop(max_msg_type, capacity, flags)
	, req_id_(0)
{}
ExampleClientEventLoop::~ExampleClientEventLoop()
{}

void ExampleClientEventLoop::registerCallbacks()
{
	ServerEventLoop::registerCallbacks();
	BABELTRADER_EV_CB(EXAMPLE_MSG_BAR, onMessageBar, MessageBar);
}

void ExampleClientEventLoop::onTCPConnect(EventMessage *msg, void *data)
{
	ServerEventLoop::onTCPConnect(msg, data);
	req_id_ = 0;
}

void ExampleClientEventLoop::onTimer(EventMessage *, void *)
{
	if (tcp_sessions_.size() == 0)
	{
		return;
	}

	if (req_id_ >= STOP_REQ_ID)
	{
		return;
	}

	NetMessageFoo foo;
	memset(&foo, 0, sizeof(foo));
	foo.head.msg_type = EXAMPLE_MSG_FOO;
	foo.head.payload_len = sizeof(foo.msg);
	foo.msg.i64 = ++req_id_;
	snprintf(foo.msg.s, sizeof(foo.msg.s), "request id: %lld", (long long)foo.msg.i64);

	for (TCPSession *session : tcp_sessions_)
	{
		LOG_INFO("send foo message: remote_addr=%s, req_id=%lld",
			session->remote_addr, (long long)foo.msg.i64);
		TCPSocketHandle *handle = (TCPSocketHandle*)session->handle;
		handle->send((NetworkSession*)session, &foo, sizeof(foo));
	}

	if (req_id_ >= STOP_REQ_ID)
	{
		LOG_INFO("stop send request, wait server idle disconnect");
	}
}

void ExampleClientEventLoop::onMessageBar(EventMessage *msg, MessageBar *data)
{
	TCPSession *session = (TCPSession*)msg->session;
	LOG_INFO(
		"on message bar: "
		"remote_addr=%s, f=%f, d=%f, s=%s",
		session->remote_addr, data->f, data->d, data->s);
}
