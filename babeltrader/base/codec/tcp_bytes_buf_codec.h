/******************************************************************************
 *  @file         tcp_bytes_buf_codec.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-19
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader TCP bytes buffer codec
 *****************************************************************************/

#ifndef BABELTRADER_TCP_BYTES_BUFFER_CODEC_H_
#define BABELTRADER_TCP_BYTES_BUFFER_CODEC_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/codec/codec.h"

NS_BABELTRADER_BEGIN

/**
 * @brief TCP bytes buffer codec
 *
 * encode: NetworkMessage -> bytes, head htonl
 * decode: bytes -> NetworkMessage, head ntohl
 */
class TcpBytesBufCodec : public Codec
{
public:
	BABELTRADER_EXPORT
	TcpBytesBufCodec();

	BABELTRADER_EXPORT
	virtual ~TcpBytesBufCodec();

	BABELTRADER_EXPORT
	virtual bool encode(
		NetworkSession *session,
		void *data,
		uint32_t data_len) override;

	BABELTRADER_EXPORT
	virtual bool decode(
		NetworkSession *session,
		void *data,
		uint32_t data_len) override;
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_BYTES_BUFFER_CODEC_H_ */
