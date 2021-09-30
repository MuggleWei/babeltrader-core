#include "event_msg_pool.h"

NS_BABELTRADER_BEGIN

EventMsgSowrPool::EventMsgSowrPool(muggle_atomic_int capacity)
	: EventMessagePool(capacity)
	, pool_(capacity)
{}
EventMsgSowrPool::~EventMsgSowrPool()
{}

void* EventMsgSowrPool::Allocate(size_t size)
{
	EventMessageBlock *event_msg = nullptr;
	if (size > sizeof(EventMessageBlock))
	{
		event_msg = (EventMessageBlock*)malloc(size);
		if (event_msg)
		{
			memset(event_msg, 0, sizeof(size));
		}

		event_msg->head.flags = MSG_FLAG_NON_POOL_MSG;
	}
	else
	{
		event_msg = (EventMessageBlock*)pool_.Allocate();
		if (event_msg)
		{
			memset(event_msg, 0, sizeof(size));
		}

		event_msg->head.pool = this;
		event_msg->head.flags = 0;
	}

	return (void*)event_msg;
}

void EventMsgSowrPool::Recycle(void *p_data)
{
	pool_.Recycle(p_data);
}

EventMsgThreadSafePool::EventMsgThreadSafePool(muggle_atomic_int capacity)
	: EventMessagePool(capacity)
	, pool_(capacity)
{}
EventMsgThreadSafePool::~EventMsgThreadSafePool()
{}

void* EventMsgThreadSafePool::Allocate(size_t size)
{
	EventMessageBlock *event_msg = nullptr;
	if (size > sizeof(EventMessageBlock))
	{
		event_msg = (EventMessageBlock*)malloc(size);
		if (event_msg)
		{
			memset(event_msg, 0, sizeof(size));
		}

		event_msg->head.flags = MSG_FLAG_NON_POOL_MSG;
	}
	else
	{
		event_msg = (EventMessageBlock*)pool_.Allocate();
		if (event_msg)
		{
			memset(event_msg, 0, sizeof(size));
		}

		event_msg->head.pool = this;
		event_msg->head.flags = 0;
	}

	return (void*)event_msg;
}

void EventMsgThreadSafePool::Recycle(void *p_data)
{
	pool_.Recycle(p_data);
}

NS_BABELTRADER_END
