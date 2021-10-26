/******************************************************************************
 *  @file         quote_server_config.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-19
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader quote server config
 *****************************************************************************/

#ifndef BABELTRADER_QUOTE_SERVER_CONFIG_H_
#define BABELTRADER_QUOTE_SERVER_CONFIG_H_

#include "babeltrader/base/defines/macro.h"

NS_BABELTRADER_BEGIN

/**
 * @brief babeltrader common quote server's config
 */
class QuoteServerConfig
{
public:
	BABELTRADER_EXPORT
	bool load(const char *file_path);

	BABELTRADER_EXPORT
	virtual bool onLoad(void *json_doc);

	BABELTRADER_EXPORT
	virtual void output();

public:
	std::string tcp_listen_ip;   //!< TCP listen host
	int         tcp_listen_port; //!< TCP listen port
	std::string udp_send_ip;     //!< UDP send ip
	int         udp_send_port;   //!< UDP send port

	uint32_t timer_interval;        //!< timer interval in seconds
	uint32_t idle_timeout;          //!< disconnect TCP/QUIC client when idle timeout, if it's 0, no idle timeout
	uint32_t event_pipe_size;       //!< event pipe size
	uint32_t recv_unit_size;        //!< number bytes per recv or recvfrom
	uint32_t max_msg_size;          //!< max message size, if it's 0, with no limit
	uint32_t socket_bytes_buf_size; //!< socket bytes buffer size
	uint32_t hints_max_connect;     //!< hints max connection socket peer
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_QUOTE_SERVER_CONFIG_H_ */
