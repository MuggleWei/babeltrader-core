/******************************************************************************
 *  @file         tcp_server_config.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-11-02
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader TCP Server config
 *****************************************************************************/

#ifndef BABELTRADER_TCP_SERVER_CONFIG_H_
#define BABELTRADER_TCP_SERVER_CONFIG_H_

#include "babeltrader/utils/utils_macro.h"
#include "babeltrader/utils/json_config.h"
#include <string>

NS_BABELTRADER_BEGIN

class TcpServerConfig : public JsonConfig
{
public:
	BABELTRADER_UTILS_EXPORT
	TcpServerConfig();

	BABELTRADER_UTILS_EXPORT
	virtual ~TcpServerConfig();

	BABELTRADER_UTILS_EXPORT
	virtual bool onLoad(void *json_doc) override;

public:
	std::string host;
	int         port;

	int msg_pool_size;
	int recv_unit_size;
	int bytes_buf_size;
	int hints_max_connect;
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_TCP_SERVER_CONFIG_H_ */
