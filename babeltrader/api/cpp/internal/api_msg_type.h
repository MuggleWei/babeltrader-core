/******************************************************************************
 *  @file         api_msg_type.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-25
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader api message type
 *****************************************************************************/

#ifndef BABELTRADER_API_MESSAGE_TYPE_H_
#define BABELTRADER_API_MESSAGE_TYPE_H_

#include "babeltrader/include/common_msg_type.h"
#include "babeltrader/api/cpp/api_macro.h"

; // for avoid pragma warning tip in vim
#pragma pack(push, 1)

NS_BABELTRADER_BEGIN

/**
 * @brief babeltrader message type
 */
enum eMessageType
{
	MSG_TYPE_API_REAL_BEGIN = MSG_TYPE_API_BEGIN,
	MSG_TYPE_API_QUOTES_REQ_SUB,
	MSG_TYPE_API_QUOTES_RSP_SUB,
	MSG_TYPE_API_QUOTES_REQ_UNSUB,
	MSG_TYPE_API_QUOTES_RSP_UNSUB,
	MSG_TYPE_API_QUOTES_SNAPSHOT,
	MSG_TYPE_API_QUOTES_TICK,
};

NS_BABELTRADER_END

#pragma pack(pop)

#endif /* ifndef BABELTRADER_MESSAGE_TYPE_H_ */
