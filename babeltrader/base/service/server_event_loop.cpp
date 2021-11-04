#include "server_event_loop.h"
#include "babeltrader/include/common_msg_type.h"
#include "babeltrader/base/defines/enum.h"

NS_BABELTRADER_BEGIN

ServerEventLoop::ServerEventLoop(int max_msg_type, int capacity, int flags)
	: EventLoop(max_msg_type, capacity, flags)
	, timer_interval_ms_(BABELTRADER_DEFAULT_SERV_TIMER_INTERVAL)
	, idle_timeout_(BABELTRADER_DEFAULT_SERV_IDLE)
{}

ServerEventLoop::~ServerEventLoop()
{}

void ServerEventLoop::run()
{
	// register callbacks
	registerCallbacks();

	// run timer
	if (timer_interval_ms_ > 0 || idle_timeout_ > 0)
	{
		if (timer_interval_ms_ <= 0)
		{
			timer_interval_ms_ = idle_timeout_ * 3;
		}
		runTimer(timer_interval_ms_);
	}

	// run event loop
	EventLoop::run();
}

void ServerEventLoop::registerCallbacks()
{
	BABELTRADER_EV_CB(MSG_TYPE_TIMER, onTimer, void);
	BABELTRADER_EV_CB(MSG_TYPE_TCP_CONNECT, onTCPConnect, void);
	BABELTRADER_EV_CB(MSG_TYPE_TCP_DISCONNECT, onTCPDicconnect, void);
}

void ServerEventLoop::setTimerMs(int timer_interval)
{
	timer_interval_ms_ = timer_interval;
}

void ServerEventLoop::setIdleTimeout(int idle_timeout)
{
	idle_timeout_ = idle_timeout;
}

void ServerEventLoop::onTimer(EventMessage *, void *)
{
	handleIdleSession();
}

void ServerEventLoop::onTCPConnect(EventMessage *msg, void *)
{
	TCPSession *session = (TCPSession*)msg->session;
	LOG_DEBUG(
		"session connection: remote_addr=%s, session_id=%llu",
		session->remote_addr, (unsigned long long)session->session_id);

	tcp_sessions_.insert(session);
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

void ServerEventLoop::handleIdleSession()
{
	if (idle_timeout_ <= 0)
	{
		return;
	}

	uint64_t curr_ts = (uint64_t)time(nullptr);
	for (TCPSession *session : tcp_sessions_)
	{
		if (curr_ts - session->last_active > (uint64_t)idle_timeout_)
		{
			LOG_DEBUG(
				"close idle connection: "
				"remote_addr=%s, curr_ts=%llu, last_active=%llu",
				session->remote_addr,
				(unsigned long long)curr_ts,
				(unsigned long long)session->last_active);
			session->peer->close();
		}
	}
}

NS_BABELTRADER_END
