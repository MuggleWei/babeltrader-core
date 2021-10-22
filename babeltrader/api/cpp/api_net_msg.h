/******************************************************************************
 *  @file         net_msg.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-10-19
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader api network message
 *****************************************************************************/

#ifndef BABELTRADER_API_NETWORK_MESSAGE_H_
#define BABELTRADER_API_NETWORK_MESSAGE_H_

#include "babeltrader/api/cpp/macro.h"

NS_BABELTRADER_BEGIN

/**
 * @brief MSG_TYPE_HEARTBEAT_PING
 */
struct NetworkMsgHeartbeatPing
{
	NetworkMessage   head; //!< network message head
	MsgHeartbeatPing msg;  //!< message
};

/**
 * @brief MSG_TYPE_HEARTBEAT_PONG
 */
struct NetworkMsgHeartbeatPong
{
	NetworkMessage   head; //!< network message head
	MsgHeartbeatPong msg;  //!< message
};

/**
 * @brief MSG_TYPE_API_QUOTES_REQ_SUB
 */
struct NetMsgReqQuoteSub
{
	NetworkMessage head; //!< network message head
	MsgReqQuoteSub msg;  //!< request message
};

/**
 * @brief MSG_TYPE_API_QUOTES_RSP_SUB
 */
struct NetMsgRspQuoteSub
{
	NetworkMessage head; //!< network message head
	MsgRspQuoteSub msg;  //!< response message
};

/**
 * @brief MSG_TYPE_API_QUOTES_REQ_UNSUB
 */
typedef NetMsgReqQuoteSub NetMsgReqQuoteUnsub;

/**
 * @brief MSG_TYPE_API_QUOTES_RSP_UNSUB
 */
typedef NetMsgRspQuoteSub NetMsgRspQuoteUnsub;

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_API_NETWORK_MESSAGE_H_ */
