/******************************************************************************
 *  @file         codec.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-18
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader codec
 *****************************************************************************/

#ifndef BABELTRADER_CODEC_H_
#define BABELTRADER_CODEC_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/defines/struct.h"

NS_BABELTRADER_BEGIN

class Codec
{
public:
	/**
	 * @brief codec constructor
	 */
	BABELTRADER_EXPORT
	Codec();

	/**
	 * @brief codec destructor
	 */
	BABELTRADER_EXPORT
	virtual ~Codec();

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
	 * @brief get next encode codec
	 *
	 * @return 
	 */
	BABELTRADER_EXPORT
	Codec* getNext();

	/**
	 * @brief get next decode codec
	 *
	 * @return 
	 */
	BABELTRADER_EXPORT
	Codec* getPrev();

	/**
	 * @brief append codec
	 *
	 * @return 
	 */
	BABELTRADER_EXPORT
	void append(Codec *codec);

protected:
	Codec *next_; //!< next codec (next encode)
	Codec *prev_; //!< prev codec (next decode)
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_CODEC_H_ */
