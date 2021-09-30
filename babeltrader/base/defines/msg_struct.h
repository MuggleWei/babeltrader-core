/******************************************************************************
 *  @file         msg_struct.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-26
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader message struct
 *****************************************************************************/

#ifndef BABELTRADER_MSG_STRUCT_H_
#define BABELTRADER_MSG_STRUCT_H_

#include "babeltrader/base/defines/macro.h"

; // for avoid pragma warning tip in vim
#pragma pack(push, 1)

NS_BABELTRADER_BEGIN

#define BABELTRADER_NET_MTU 1400

#define BABELTRADER_INSTRUMENT_ID_LEN 32
#define BABELTRADER_PRODUCT_ID_LEN 32

#define BABELTRADER_UP_ERR (-1)

/////////////////////// struct ///////////////////////

/**
 * @brief traidng instrument
 */
struct Instrument
{
	uint16_t api;          //!< EnumApi
	uint16_t exchange;     //!< EnumExchange
	uint8_t  product_type; //!< EnumProductType
	uint8_t  reserve1;     //!< reserve field
	uint8_t  reserve2;     //!< reserve field
	uint8_t  reserve3;     //!< reserve field
	char product_id[BABELTRADER_PRODUCT_ID_LEN];       //!< product id in exchange
	char instrument_id[BABELTRADER_INSTRUMENT_ID_LEN]; //!< instrument id in exchange
};

/////////////////////// message struct ///////////////////////

/**
 * @brief empty message
 */
struct MsgEmpty
{};

/**
 * @brief error information
 */
struct MsgErrorInfo
{
	int64_t err_id;       //!< error id, if it's BABELTRADER_UP_ERR, then see uperr_id
	int64_t uperr_id;     //!< upstream error id
	char    err_msg[512]; //!< error message
};

/**
 * @brief heartbeat ping message
 */
struct MsgHeartbeatPing
{
	uint64_t sec;  //!< timestamp second
};

/**
 * @brief heartbeat pong message
 */
struct MsgHeartbeatPong
{
	uint64_t sec;  //!< timestamp second
};

/////////////////////// quote message struct ///////////////////////

/**
 * @brief request sub/unsub quote message
 */
struct MsgReqQuoteSub
{
	int64_t    req_id;     //!< request id from api
	int32_t    quote_type; //!< quote type
	Instrument instrument; //!< instrument
};

/**
 * @brief response sub/unsub quote message
 */
struct MsgRspQuoteSub
{
	MsgReqQuoteSub req;      //!< request message
	MsgErrorInfo   err_info; //!< error info
};

NS_BABELTRADER_END

#pragma pack(pop)

#endif /* ifndef BABELTRADER_NET_STRUCT_H_ */
