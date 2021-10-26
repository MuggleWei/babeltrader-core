/******************************************************************************
 *  @file         server_event_loop.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-10-22
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader server event loop
 *****************************************************************************/

#ifndef BABELTRADER_SERVER_EVENT_LOOP_H_
#define BABELTRADER_SERVER_EVENT_LOOP_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/service/event_loop.h"
#include "babeltrader/base/defines/struct.h"

NS_BABELTRADER_BEGIN

class ServerEventLoop : public EventLoop
{
public:
	/**
	 * @brief Server event loop constructor
	 *
	 * @param max_msg_type  max message type id
	 * @param capacity      capacity of channel
	 * @param flags         flags of channel
	 */
	BABELTRADER_EXPORT
	ServerEventLoop(int max_msg_type, int capacity, int flags);

	/**
	 * @brief Server event loop destructor
	 */
	BABELTRADER_EXPORT
	virtual ~ServerEventLoop();

	/**
	 * @brief run server event loop
	 */
	BABELTRADER_EXPORT
	virtual void run();

	/**
	 * @brief register callbacks
	 */
	BABELTRADER_EXPORT
	virtual void registerCallbacks();

	//////////////// calllbacks ////////////////
	BABELTRADER_EXPORT
	virtual void onTimer(EventMessage *msg, void *data);

	BABELTRADER_EXPORT
	virtual void onTCPConnect(EventMessage *msg, void *data);

	BABELTRADER_EXPORT
	virtual void onTCPDicconnect(EventMessage *msg, void *data);

protected:
	std::set<TCPSession*> tcp_sessions_;
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_SERVER_EVENT_LOOP_H_ */
