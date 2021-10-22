/******************************************************************************
 *  @file         common_event_message.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-17
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader common event message
 *****************************************************************************/

#ifndef BABELTRADER_COMMON_EVENT_MESSAGE_H_
#define BABELTRADER_COMMON_EVENT_MESSAGE_H_

#include "babeltrader/include/common_macro.h"
#include <stdint.h>

NS_BABELTRADER_BEGIN

enum eMessageFlags
{
	MSG_FLAG_NULL = 0,
	MSG_FLAG_NON_POOL_MSG = 1,  //!< allocate without pool
};

/**
 * @brief event message head
 */
struct EventMessage
{
	uint64_t msg_type; //!< message type
	uint64_t flags;    //!< message flag in eMessageFlags
	void     *pool;    //!< memory pool that allocate this message
	void     *session; //!< session or context
};

/**
 * @brief event message block
 */
struct EventMessageBlock
{
	EventMessage head; //!< event message head
	char placeholder[2048-sizeof(EventMessage)]; //!< placeholder for payload
};

struct EventMsgDataPtr
{
	EventMessage head;  //!< event message head
	void         *data; //!< data pointer
};

#define BABELTRADER_EV_MSG_SIZE(T) (sizeof(T)+sizeof(EventMessage))

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_EVENT_MESSAGE_H_ */

