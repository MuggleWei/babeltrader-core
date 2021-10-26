/******************************************************************************
 *  @file         tcp_socket_handle.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-17
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader TCP Socket Handle
 *****************************************************************************/

#ifndef BABELTRADER_TCP_SOCKET_HANDLE_H_
#define BABELTRADER_TCP_SOCKET_HANDLE_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/service/socket_handle.h"
#include "babeltrader/base/memory/event_msg_pool.h"
#include "babeltrader/base/service/event_loop.h"
#include "babeltrader/base/service/session_manager.h"
#include <set>

NS_BABELTRADER_BEGIN

class TCPSocketHandle : public SocketHandle
{
public:
	BABELTRADER_EXPORT
	TCPSocketHandle();

	BABELTRADER_EXPORT
	virtual ~TCPSocketHandle();

	BABELTRADER_EXPORT
	virtual void onListen(muggle_socket_event_t *ev, muggle::SocketPeer *peer) override;

	BABELTRADER_EXPORT
	virtual void onConnect(muggle_socket_event_t *ev, muggle::SocketPeer *peer) override;

	BABELTRADER_EXPORT
	virtual void onMessage(muggle_socket_event_t *ev, muggle::SocketPeer *peer) override;

	BABELTRADER_EXPORT
	virtual void onError(muggle_socket_event_t *ev, muggle::SocketPeer *peer) override;

	BABELTRADER_EXPORT
	virtual void onClose(muggle_socket_event_t *ev, muggle::SocketPeer *peer) override;

	BABELTRADER_EXPORT
	virtual void onTimer(muggle_socket_event_t *ev) override;

	BABELTRADER_EXPORT
	virtual void onRecv(NetworkSession *session, void *data, uint32_t data_len) override;

	BABELTRADER_EXPORT
	virtual void onSend(NetworkSession *session, void *data, uint32_t data_len) override;

	BABELTRADER_EXPORT
	virtual void recv(NetworkSession *session) override;

	BABELTRADER_EXPORT
	virtual void send(NetworkSession *session, void *data, uint32_t data_len) override;

	BABELTRADER_EXPORT
	void setSessionPool(muggle::IMemoryPool<TCPSession> *pool);

	BABELTRADER_EXPORT
	void setEventMessagePool(EventMessagePool *pool);

	BABELTRADER_EXPORT
	void setEventLoop(EventLoop *event_loop);

	/**
	 * @brief set size of peer's bytes buffer
	 *
	 * @param bytes_buf_size  bytes buffer size
	 */
	BABELTRADER_EXPORT
	void setBytesBufferSize(uint32_t bytes_buf_size);

	/**
	 * @brief set recv number of bytes per socket recv
	 *
	 * @param recv_unit_size recv number of bytes per socket recv
	 */
	BABELTRADER_EXPORT
	void setRecvUnitSize(uint32_t recv_unit_size);

	/**
	 * @brief set allowed max message size
	 *
	 * @param max_msg_size allowed max message size
	 */
	BABELTRADER_EXPORT
	void setMaxMsgSize(uint32_t max_msg_size);

	/**
	 * @brief set connection role
	 *
	 * @param conn_role  connection role
	 */
	BABELTRADER_EXPORT
	void setConnRole(uint32_t conn_role);

	/**
	 * @brief set connection handle id
	 *
	 * @param conn_id  connection handle id
	 */
	BABELTRADER_EXPORT
	void setConnHandleId(uint32_t conn_handle_id);

private:
	BABELTRADER_EXPORT
	TCPSession* newSession(muggle::SocketPeer *peer);

protected:
	muggle::IMemoryPool<TCPSession> *session_pool_; //!< session pool

	EventMessagePool *msg_pool_;   //!< event message pool
	EventLoop        *event_loop_; //!< event loop

	SessionManager session_mgr_;

	uint32_t bytes_buf_size_;  //!< socket bytes buffer size
	uint32_t recv_unit_size_;  //!< number of bytes from socket per recv
	uint32_t max_msg_size_;    //!< allowed max message size, if == 0, with no limit

	uint32_t conn_role_;       //!< connection role
	uint32_t conn_handle_id_;  //!< connection handle id
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_TCP_SERVER_HANDLE_H_ */
