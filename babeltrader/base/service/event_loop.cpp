#include "event_loop.h"
#include <thread>
#include "babeltrader/include/common_msg_struct.h"
#include "babeltrader/include/common_msg_type.h"
#include "babeltrader/base/memory/event_msg_pool.h"

NS_BABELTRADER_BEGIN

EventLoop::EventLoop(uint32_t capacity, int flags)
	: chan_(capacity, flags)
	, dispatcher_(nullptr)
{}

EventLoop::~EventLoop()
{}

void EventLoop::setDispatcher(MessageDispatcher *dispatcher)
{
	dispatcher_ = dispatcher;
}

void EventLoop::run()
{
	if (dispatcher_ == nullptr)
	{
		LOG_ERROR("run without dispatcher");
		return;
	}

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

void EventLoop::onMessage(EventMessage *msg)
{
	if (msg)
	{
		if (!dispatcher_->OnMessage(msg->msg_type, (void*)msg))
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

void EventLoop::runTimer(uint32_t interval_sec)
{
	if (interval_sec == 0)
	{
		return;
	}

	std::thread th([&, interval_sec]{
		EventMsgSowrPool msg_pool(16);
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::seconds(interval_sec));
			EventMessage *event_msg = 
				(EventMessage*)msg_pool.Allocate(BABELTRADER_EV_MSG_SIZE(MsgEmpty));

			event_msg->msg_type = MSG_TYPE_TIMER;
			push(event_msg);
		}
	});
	th.detach();
}

NS_BABELTRADER_END
