#include "event_loop.h"
#include <thread>
#include "babeltrader/include/common_msg_struct.h"
#include "babeltrader/include/common_msg_type.h"
#include "babeltrader/base/memory/event_msg_pool.h"

NS_BABELTRADER_BEGIN

EventLoop::EventLoop(int max_msg_type, uint32_t capacity, int flags)
	: chan_(capacity, flags)
	, dispatcher_(max_msg_type)
{}

EventLoop::~EventLoop()
{}

void EventLoop::run()
{
	while (true)
	{
		EventMessage *msg = (EventMessage*)chan_.read();
		onMessage(msg);
	}
}

int EventLoop::push(EventMessage *msg)
{
	return chan_.write((void*)msg);
}

void EventLoop::runTimer(uint32_t interval_ms)
{
	if (interval_ms == 0)
	{
		return;
	}

	std::thread th([&, interval_ms]{
		int cap = 2000 / interval_ms;
		cap = cap > 16 ? cap : 16;

		EventMsgSowrPool msg_pool(cap);
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
			EventMessage *event_msg = 
				(EventMessage*)msg_pool.Allocate(BABELTRADER_EV_MSG_SIZE(MsgEmpty));

			event_msg->msg_type = MSG_TYPE_TIMER;
			push(event_msg);
		}
	});
	th.detach();
}

void EventLoop::onMessage(EventMessage *msg)
{
	if (msg)
	{
		if (!dispatcher_.OnMessage(msg->msg_type, (void*)msg))
		{
			LOG_WARNING(
				"event loop failed dispatch message: msg_type=%lu",
				(unsigned long)msg->msg_type);
		}
		clearMessage(msg);
	}
}

void EventLoop::clearMessage(EventMessage *msg)
{
	if (msg->flags & MSG_FLAG_NON_POOL_MSG)
	{
		free(msg);
	}
	else
	{
		EventMessagePool *pool = (EventMessagePool*)msg->pool;
		if (pool)
		{
			pool->Recycle(msg);
		}
		else
		{
			free(msg);
		}
	}
}

NS_BABELTRADER_END
