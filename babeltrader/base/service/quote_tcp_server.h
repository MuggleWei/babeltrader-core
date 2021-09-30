/******************************************************************************
 *  @file         quote_tcp_server.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-09-06
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader quote tcp server
 *****************************************************************************/

#ifndef BABELTRADER_QUOTE_TCP_SERVER_H_
#define BABELTRADER_QUOTE_TCP_SERVER_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/codec/codec.h"
#include "babeltrader/base/service/quote_server_config.h"
#include "babeltrader/base/service/event_loop.h"

NS_BABELTRADER_BEGIN

class QuoteTcpServer
{
public:
	/**
	 * @brief QuoteTcpServer constructor
	 */
	QuoteTcpServer();

	/**
	 * @brief QuoteTcpServer destructor
	 */
	virtual ~QuoteTcpServer();

	/**
	 * @brief set quote server config
	 *
	 * @param cfg  quote config
	 */
	void setQuoteConfig(QuoteServerConfig *cfg);

	/**
	 * @brief set event loop
	 *
	 * @param ev_loop
	 */
	void setEventLoop(EventLoop *ev_loop);

	/**
	 * @brief set endianness codec
	 *
	 * @param codec endian codec
	 */
	void setEndianCodec(Codec *codec);

	/**
	 * @brief run TCP server
	 */
	void run();

private:
	QuoteServerConfig *quote_cfg_;    //!< quote server config
	EventLoop         *ev_loop_;      //!< event loop
	Codec             *endian_codec_; //!< endianess codec
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_QUOTE_TCP_SERVER_H_ */
