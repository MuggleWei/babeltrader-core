/******************************************************************************
 *  @file         msg_type.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-25
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader message type
 *****************************************************************************/

#ifndef BABELTRADER_MESSAGE_TYPE_H_
#define BABELTRADER_MESSAGE_TYPE_H_

#include "babeltrader/base/defines/macro.h"

; // for avoid pragma warning tip in vim
#pragma pack(push, 1)

NS_BABELTRADER_BEGIN

/**
 * @brief babeltrader message type
 */
enum eMessageType
{
	MSG_TYPE_NULL = 0,
	MSG_TYPE_TIMER,          //!< timer
	MSG_TYPE_HEARTBEAT_PING, //!< heartbeat ping
	MSG_TYPE_HEARTBEAT_PONG, //!< heartbeat pong
	MSG_TYPE_TCP_CONNECT,    //!< TCP connection
	MSG_TYPE_TCP_DISCONNECT, //!< TCP disconnection

	MSG_TYPE_API_COMMON_BEGIN = 128,
	MSG_TYPE_API_QUOTES_REQ_SUB,
	MSG_TYPE_API_QUOTES_RSP_SUB,
	MSG_TYPE_API_QUOTES_REQ_UNSUB,
	MSG_TYPE_API_QUOTES_RSP_UNSUB,
	MSG_TYPE_API_QUOTES_SNAPSHOT,
	MSG_TYPE_API_QUOTES_TICK,

	MSG_TYPE_UPSTREAM_API_BEGIN = 256,
	MSG_TYPE_USER_BEGIN = 1000,
};

NS_BABELTRADER_END

#pragma pack(pop)

#endif /* ifndef BABELTRADER_MESSAGE_TYPE_H_ */
