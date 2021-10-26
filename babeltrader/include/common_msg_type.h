/******************************************************************************
 *  @file         common_msg_type.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-10-20
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader base message type
 *****************************************************************************/

#ifndef BABELTRADER_COMMON_MSG_TYPE_H_
#define BABELTRADER_COMMON_MSG_TYPE_H_

#include "babeltrader/include/common_macro.h"

NS_BABELTRADER_BEGIN

enum
{
	MSG_TYPE_NULL = 0,

	MSG_TYPE_COMMON_BEGIN,

	MSG_TYPE_TIMER,          //!< timer
	MSG_TYPE_HEARTBEAT_PING, //!< heartbeat ping
	MSG_TYPE_HEARTBEAT_PONG, //!< heartbeat pong
	MSG_TYPE_TCP_CONNECT,    //!< TCP connection
	MSG_TYPE_TCP_DISCONNECT, //!< TCP disconnection

	MSG_TYPE_COMMON_END = 256,

	MSG_TYPE_API_BEGIN,
	MSG_TYPE_API_END = 1024,

	MSG_TYPE_UPSTREAM_API_BEGIN,
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_BASE_MSG_TYPE_H_ */
