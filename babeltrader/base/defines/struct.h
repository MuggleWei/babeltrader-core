/******************************************************************************
 *  @file         struct.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-01
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader struct
 *****************************************************************************/

#ifndef BABELTRADER_STRUCT_H_
#define BABELTRADER_STRUCT_H_

#include "babeltrader/base/defines/macro.h"

NS_BABELTRADER_BEGIN

/**
 * @brief network address
 */
struct NetworkAddr
{
	char     host[MUGGLE_SOCKET_ADDR_STRLEN]; //!< ip address
	uint16_t port;                            //!< port
};

/**
 * @brief network session
 */
struct NetworkSession
{
	muggle::SocketPeer *peer;      //!< socket peer pointer
	uint64_t           session_id; //!< session id
	char remote_addr[MUGGLE_SOCKET_ADDR_STRLEN]; //!< remote address string
};

/**
 * @brief TCP session
 */
struct TCPSession
{
	muggle::SocketPeer *peer;      //!< socket peer pointer
	uint64_t           session_id; //!< session id
	char remote_addr[MUGGLE_SOCKET_ADDR_STRLEN]; //!< remote address string

	muggle_bytes_buffer_t bytes_buf;      //!< bytes buffer

	uint32_t recv_unit_size; //!< recv unit size
	uint32_t max_msg_size;   //!< allowed max message size, if == 0, with no limit
	uint64_t last_active;    //!< last active timestamp
	void     *handle;        //!< session handle
	void     *user_data;     //!< user data
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_STRUCT_H_ */
