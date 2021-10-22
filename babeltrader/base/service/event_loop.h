/******************************************************************************
 *  @file         event_loop.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-17
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader event loop
 *****************************************************************************/

#ifndef BABELTRADER_EVENT_LOOP_H_
#define BABELTRADER_EVENT_LOOP_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/include/common_event_message.h"
#include "babeltrader/base/service/message_dispatcher.hpp"

#include <set>

NS_BABELTRADER_BEGIN

class EventLoop
{
public:
	/**
	 * @brief Event loop constructor
	 *
	 * @param capacity  capacity of channel
	 * @param flags     flags of channel
	 */
	BABELTRADER_EXPORT
	EventLoop(uint32_t capacity, int flags);

	/**
	 * @brief Event loop destructor
	 */
	BABELTRADER_EXPORT
	virtual ~EventLoop();

	/**
	 * @brief 
	 *
	 * @param dispatcher
	 */
	BABELTRADER_EXPORT
	void setDispatcher(MessageDispatcher *dispatcher);

	/**
	 * @brief run event loop
	 */
	BABELTRADER_EXPORT
	void run();

	/**
	 * @brief push message into event loop
	 *
	 * @param msg  event message
	 *
	 * @return 
	 *     - on success, return 0
	 *     - on failed, return error code in muggle/c/base/err.h
	 */
	BABELTRADER_EXPORT
	int push(EventMessage *msg);

	/**
	 * @brief on receive event message
	 *
	 * @param msg  event message
	 */
	BABELTRADER_EXPORT
	virtual void onMessage(EventMessage *msg);

	/**
	 * @brief clear message after callback
	 *
	 * @param msg  event message
	 */
	BABELTRADER_EXPORT
	virtual void clearMessage(EventMessage *msg);

	/**
	 * @brief run timer
	 *
	 * @param interval_sec timer interval seconds
	 */
	BABELTRADER_EXPORT
	virtual void runTimer(uint32_t interval_sec);

protected:
	muggle::Channel chan_;
	MessageDispatcher *dispatcher_;
};

#define BABELTRADER_EV_CB(msg_type, func, T) \
{ \
	auto f = [&](EventMessage *ev_msg) { \
		this->func(ev_msg, (T*)(ev_msg+1)); \
	}; \
	dispatcher_.Register<EventMessage>(msg_type, f); \
}

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_EVENT_LOOP_H_ */
