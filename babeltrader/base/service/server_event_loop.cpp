#include "server_event_loop.h"
#include "babeltrader/include/common_msg_type.h"

NS_BABELTRADER_BEGIN

ServerEventLoop::ServerEventLoop(int max_msg_type, int capacity, int flags)
	: EventLoop(max_msg_type, capacity, flags)
{}

ServerEventLoop::~ServerEventLoop()
{}

void ServerEventLoop::run()
{
	// register callbacks
	registerCallbacks();

	// run event loop
	EventLoop::run();
}

void ServerEventLoop::registerCallbacks()
{
	BABELTRADER_EV_CB(MSG_TYPE_TIMER, onTimer, void);
	BABELTRADER_EV_CB(MSG_TYPE_TCP_CONNECT, onTCPConnect, void);
	BABELTRADER_EV_CB(MSG_TYPE_TCP_DISCONNECT, onTCPDicconnect, void);
}

void ServerEventLoop::onTimer(EventMessage *, void *)
{}

void ServerEventLoop::onTCPConnect(EventMessage *msg, void *)
{
	TCPSession *session = (TCPSession*)msg->session;
	LOG_DEBUG(
		"session connection: remote_addr=%s, session_id=%llu",
		session->remote_addr, (unsigned long long)session->session_id);

	tcp_sessions_.insert(session);
	session->last_active = (uint64_t)time(nullptr);
}

void ServerEventLoop::onTCPDicconnect(EventMessage *msg, void *)
{
	TCPSession *session = (TCPSession*)msg->session;
	LOG_DEBUG(
		"session disconnection: remote_addr=%s, session_id=%llu",
		session->remote_addr, (unsigned long long)session->session_id);

	tcp_sessions_.erase(session);
	session->peer->release();
}

NS_BABELTRADER_END
