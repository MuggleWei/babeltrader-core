/******************************************************************************
 *  @file         common_net_message.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-17
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader network message
 *****************************************************************************/

#ifndef BABELTRADER_COMMON_NETWORK_MESSAGE_H_
#define BABELTRADER_COMMON_NETWORK_MESSAGE_H_

#include "babeltrader/include/common_macro.h"
#include <stdint.h>

; // for avoid pragma warning tip in vim
#pragma pack(push, 1)

NS_BABELTRADER_BEGIN

#define BABELTRADER_NET_MTU 1400

/**
 * @brief network message head
 */
struct NetworkMessage
{
	uint32_t msg_type;     //!< message type
	uint32_t payload_len;  //!< payload data length(not include header)
};

#define BABELTRADER_NET_PAYLOAD_SIZE(T) (sizeof(T) - sizeof(NetworkMessage))

#define BABELTRADER_FILLUP_NET_HEAD(net_msg, msgtype) \
{ \
	memset(&net_msg, 0, sizeof(net_msg)); \
	net_msg.head.msg_type = msgtype; \
	net_msg.head.payload_len = BABELTRADER_NET_PAYLOAD_SIZE(net_msg); \
}

/**
 * @brief network message block
 */
struct NetworkMsgBlock
{
	NetworkMessage head; //!< network message head
	char placeholder[BABELTRADER_NET_MTU-sizeof(NetworkMessage)]; //!< placeholder for payload
};

NS_BABELTRADER_END

#pragma pack(pop)

#endif /* ifndef BABELTRADER_NETWORK_MESSAGE_H_ */
