/******************************************************************************
 *  @file         codec_chain.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-27
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader codec chain
 *****************************************************************************/

#ifndef BABELTRADER_CODEC_CHAIN_H_
#define BABELTRADER_CODEC_CHAIN_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/codec/codec.h"
#include "babeltrader/base/codec/codec_callback.h"

NS_BABELTRADER_BEGIN

class CodecChain
{
public:
	/**
	 * @brief codec chain constructor
	 */
	BABELTRADER_EXPORT
	CodecChain();

	/**
	 * @brief codec chain destructor
	 */
	BABELTRADER_EXPORT
	virtual ~CodecChain();

	/**
	 * @brief encode data
	 *
	 * @param session   network sesssion
	 * @param data      data need to be encoded
	 * @param data_len  input data length
	 *
	 * @return boolean value
	 */
	BABELTRADER_EXPORT
	virtual bool encode(
		NetworkSession *session,
		void *data,
		uint32_t data_len);

	/**
	 * @brief decode data
	 *
	 * @param session   network sesssion
	 * @param data      data need to be decoded
	 * @param data_len  length of input data
	 *
	 * @return boolean value
	 */
	BABELTRADER_EXPORT
	virtual bool decode(
		NetworkSession *session,
		void *data,
		uint32_t data_len);

	/**
	 * @brief append codec
	 *
	 * @param codec  codec pointer
	 */
	BABELTRADER_EXPORT
	void appendCodec(Codec *codec);

	/**
	 * @brief set all encode complete callback
	 *
	 * @param cb
	 */
	BABELTRADER_EXPORT
	void setEncodeCallback(func_codec_cb &cb);

	/**
	 * @brief set all decode complete callback
	 *
	 * @param cb
	 */
	BABELTRADER_EXPORT
	void setDecodeCallback(func_codec_cb &cb);

private:
	CodecCallback encode_cb_;
	CodecCallback decode_cb_;
	Codec *encode_head_;
	Codec *decode_head_;
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_CODEC_CHAIN_H_ */
