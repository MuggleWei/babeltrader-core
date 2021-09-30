/******************************************************************************
 *  @file         endian_conv.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-09-07
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader endian convert
 *****************************************************************************/

#ifndef BABELTRADER_ENDIAN_CONV_H_
#define BABELTRADER_ENDIAN_CONV_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/defines/net_message.h"

NS_BABELTRADER_BEGIN

class EndianConv
{
public:
	/**
	 * @brief endian conv constructor
	 */
	BABELTRADER_EXPORT
	EndianConv();

	/**
	 * @brief endian conv destructor
	 */
	BABELTRADER_EXPORT
	virtual ~EndianConv();

	/**
	 * @brief set network protocol endianness
	 *
	 * NOTE:
	 * usually, Big-endianness is the dominant ordering in networking protocols.
	 * babeltrader use Little-endianness as ordering for networking protocol by default.
	 * use this function to change default networking protocol endianness
	 */
	BABELTRADER_EXPORT
	void setNetEndian(int net_endian);

	/**
	 * @brief whether or not need swap endianness
	 *
	 * @return boolean value
	 */
	BABELTRADER_EXPORT
	bool needSwap();

	/**
	 * @brief swap endianness network message head
	 *
	 * @param head network message head
	 */
	BABELTRADER_EXPORT
	void swapEndian(NetworkMessage &head);

	/**
	 * @brief swap endianness - NetworkMsgHeartbeatPing
	 *
	 * @param msg  NetworkMsgHeartbeatPing
	 */
	BABELTRADER_EXPORT
	void swapEndian(NetworkMsgHeartbeatPing &msg);

	/**
	 * @brief swap endianness - NetworkMsgHeartbeatPong
	 *
	 * @param msg  NetworkMsgHeartbeatPong
	 */
	BABELTRADER_EXPORT
	void swapEndian(NetworkMsgHeartbeatPong &msg);

	/**
	 * @brief swap endianness - NetMsgReqQuoteSub
	 *
	 * @param msg  NetMsgReqQuoteSub
	 */
	BABELTRADER_EXPORT
	void swapEndian(NetMsgReqQuoteSub &msg);

	/**
	 * @brief swap endianness - NetMsgRspQuoteSub
	 *
	 * @param msg  NetMsgRspQuoteSub
	 */
	BABELTRADER_EXPORT
	void swapEndian(NetMsgRspQuoteSub &msg);


protected:

	/**
	 * @brief swap endianness
	 *
	 * @param i16 int16
	 *
	 * @return int16 value after swap endianness
	 */
	BABELTRADER_EXPORT
	int16_t swap(int16_t i16);

	/**
	 * @brief swap endianness
	 *
	 * @param u16 uint16
	 *
	 * @return uint16 value after swap endianness
	 */
	BABELTRADER_EXPORT
	uint16_t swap(uint16_t u16);

	/**
	 * @brief swap endianness
	 *
	 * @param i32 int32
	 *
	 * @return int32 value after swap endianness
	 */
	BABELTRADER_EXPORT
	int32_t swap(int32_t i32);

	/**
	 * @brief swap endianness
	 *
	 * @param u32 uint32
	 *
	 * @return uint32 value after swap endianness
	 */
	BABELTRADER_EXPORT
	uint32_t swap(uint32_t u32);

	/**
	 * @brief swap endianness
	 *
	 * @param i64 int64
	 *
	 * @return int64 value after swap endianness
	 */
	BABELTRADER_EXPORT
	int64_t swap(int64_t i64);

	/**
	 * @brief swap endianness
	 *
	 * @param u64 uint64
	 *
	 * @return uint64 value after swap endianness
	 */
	BABELTRADER_EXPORT
	uint64_t swap(uint64_t u64);

	/**
	 * @brief swap endianness - Instrument
	 *
	 * @param msg  Instrument
	 */
	BABELTRADER_EXPORT
	void swapEndian(Instrument &msg);

	/**
	 * @brief swap endianness - MsgErrorInfo
	 *
	 * @param msg  MsgErrorInfo
	 */
	BABELTRADER_EXPORT
	void swapEndian(MsgErrorInfo &msg);

	/**
	 * @brief swap endianness - MsgHeartbeatPing
	 *
	 * @param msg  MsgHeartbeatPing
	 */
	BABELTRADER_EXPORT
	void swapEndian(MsgHeartbeatPing &msg);

	/**
	 * @brief swap endianness - MsgHeartbeatPong
	 *
	 * @param msg  MsgHeartbeatPong
	 */
	BABELTRADER_EXPORT
	void swapEndian(MsgHeartbeatPong &msg);

	/**
	 * @brief swap endianness - MsgReqQuoteSub
	 *
	 * @param msg  MsgReqQuoteSub
	 */
	BABELTRADER_EXPORT
	void swapEndian(MsgReqQuoteSub &msg);

	/**
	 * @brief swap endianness - NetMsgRspQuoteSub
	 *
	 * @param msg  NetMsgRspQuoteSub
	 */
	BABELTRADER_EXPORT
	void swapEndian(MsgRspQuoteSub &msg);


protected:
	int endian_;     //!< endianness in host
	int net_endian_; //!< endianness for network
};

#define BABELTRADER_SWAP_ENDIAN(conv, value) \
if (conv.needSwap()) \
{ \
	conv.swapEndian(value); \
}

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_ENDIAN_CONV_H_ */
