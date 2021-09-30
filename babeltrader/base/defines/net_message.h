/******************************************************************************
 *  @file         net_message.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-17
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader network message
 *****************************************************************************/

#ifndef BABELTRADER_NETWORK_MESSAGE_H_
#define BABELTRADER_NETWORK_MESSAGE_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/defines/msg_struct.h"

; // for avoid pragma warning tip in vim
#pragma pack(push, 1)

NS_BABELTRADER_BEGIN

/**
 * @brief network message head
 */
struct NetworkMessage
{
	uint32_t msg_type;     //!< message type
	uint32_t payload_len;  //!< payload data length(not include header)
};

#define BABELTRADER_NET_PAYLOAD_SIZE(T) (sizeof(T) - sizeof(NetworkMessage))

/**
 * @brief network message block
 */
struct NetworkMsgBlock
{
	NetworkMessage head; //!< network message head
	char placeholder[BABELTRADER_NET_MTU-sizeof(NetworkMessage)]; //!< placeholder for payload
};

/**
 * @brief network message data pointer
 *
 * NOTE: this struct just use in process internal
 */
struct NetworkMsgDataPtr
{
	NetworkMessage head; //!< network message head

	void *data; //!< data pointer
};

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

#pragma pack(pop)

#endif /* ifndef BABELTRADER_NETWORK_MESSAGE_H_ */
