/******************************************************************************
 *  @file         codec_callback.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-27
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader codec callback
 *****************************************************************************/

#ifndef BABELTRADER_CODEC_CALLBACK_H_
#define BABELTRADER_CODEC_CALLBACK_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/codec/codec.h"

#include <functional>

NS_BABELTRADER_BEGIN

typedef std::function<bool(NetworkSession*,void*,uint32_t)> func_codec_cb; //!< callback on all decode completed

class CodecCallback : public Codec
{
public:
	/**
	 * @brief codec callback constructor
	 */
	BABELTRADER_EXPORT
	CodecCallback();

	/**
	 * @brief codec callback destructor
	 */
	BABELTRADER_EXPORT
	virtual ~CodecCallback();

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
	func_codec_cb encode_cb_; //!< encode callback
	func_codec_cb decode_cb_; //!< decode callback
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_CODEC_CALLBACK_H_ */
