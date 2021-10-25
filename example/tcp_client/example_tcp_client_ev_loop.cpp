#include "example_tcp_client_ev_loop.h"

ExampleClientEventLoop::ExampleClientEventLoop(int max_msg_type, int capacity, int flags)
	: ServerEventLoop(max_msg_type, capacity, flags)
	, req_id_(0)
{}
ExampleClientEventLoop::~ExampleClientEventLoop()
{}

void ExampleClientEventLoop::registerCallbacks()
{
	ServerEventLoop::registerCallbacks();
}

void ExampleClientEventLoop::onTimer(EventMessage *, void *)
{
	LOG_INFO("on timer......");

	NetMessageFoo foo;
	memset(&foo, 0, sizeof(foo));
	foo.head.msg_type = EXAMPLE_MSG_FOO;
	foo.head.payload_len = sizeof(foo.msg);
	foo.msg.i64 = ++req_id_;
	snprintf(foo.msg.s, sizeof(foo.msg.s), "request id: %lld", (long long)foo.msg.i64);

	NetMessageBar bar;
	memset(&bar, 0, sizeof(bar));
	bar.head.msg_type = EXAMPLE_MSG_BAR;
	bar.head.payload_len = sizeof(bar.msg);
	bar.msg.d = (double)req_id_;
	bar.msg.f = (float)req_id_;
	snprintf(bar.msg.s, sizeof(bar.msg.s), "f=%.2f, d=%.2f", bar.msg.f, bar.msg.d);

	for (TCPSession *session : tcp_sessions_)
	{
		TCPSocketHandle *handle = (TCPSocketHandle*)session->handle;
		handle->send((NetworkSession*)session, &foo, sizeof(foo));
		handle->send((NetworkSession*)session, &bar, sizeof(bar));
	}
}
