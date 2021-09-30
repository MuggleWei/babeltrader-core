/******************************************************************************
 *  @file         event_msg_pool.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-18
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader event message pool
 *****************************************************************************/

#ifndef BABELTRADER_EVENT_MESSAGE_POOL_H_
#define BABELTRADER_EVENT_MESSAGE_POOL_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/defines/event_message.h"

NS_BABELTRADER_BEGIN

class EventMessagePool
{
public:
	BABELTRADER_EXPORT
	EventMessagePool(muggle_atomic_int) {}
	BABELTRADER_EXPORT
	virtual ~EventMessagePool() {}

	/**
	 * @brief allocate memory
	 *
	 * @param size size of block
	 *
	 * @return allocated memory space
	 */
	BABELTRADER_EXPORT
	virtual void* Allocate(size_t size) = 0;

	/**
	 * @brief recycle memory space
	 *
	 * @param p_data pointer to memory space
	 */
	BABELTRADER_EXPORT
	virtual void Recycle(void *p_data) = 0;
};

class EventMsgSowrPool : public EventMessagePool
{
public:
	BABELTRADER_EXPORT
	EventMsgSowrPool(muggle_atomic_int capacity);
	BABELTRADER_EXPORT
	virtual ~EventMsgSowrPool();

	BABELTRADER_EXPORT
	virtual void* Allocate(size_t size) override;

	BABELTRADER_EXPORT
	virtual void Recycle(void *p_data) override;

private:
	muggle::SowrMemoryPool<EventMessageBlock> pool_;
};

class EventMsgThreadSafePool : public EventMessagePool
{
public:
	BABELTRADER_EXPORT
	EventMsgThreadSafePool(muggle_atomic_int capacity);
	BABELTRADER_EXPORT
	virtual ~EventMsgThreadSafePool();

	BABELTRADER_EXPORT
	virtual void* Allocate(size_t size) override;

	BABELTRADER_EXPORT
	virtual void Recycle(void *p_data) override;

private:
	muggle::ThreadSafeMemoryPool<EventMessageBlock> pool_;
};

#define BABELTRADER_EV_MSG_ALLOC(pool, msgtype, T) \
EventMessage *ev_msg = (EventMessage*)msg_pool_->Allocate(BABELTRADER_EV_MSG_SIZE(T)); \
if (ev_msg == nullptr) \
{ \
	LOG_ERROR("event message pool failed alloc " #T); \
	return; \
} \
ev_msg->msg_type = msgtype;

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_EVENT_MESSAGE_POOL_H_ */
