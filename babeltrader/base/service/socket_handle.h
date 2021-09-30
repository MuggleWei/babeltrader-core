/******************************************************************************
 *  @file         socket_handle.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-18
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader socket handle
 *****************************************************************************/

#ifndef BABELTRADER_SOCKET_HANDLE_H_
#define BABELTRADER_SOCKET_HANDLE_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/codec/codec_chain.h"
#include <vector>

NS_BABELTRADER_BEGIN

class SocketHandle : public muggle::SocketHandle
{
public:
	BABELTRADER_EXPORT
	SocketHandle();

	BABELTRADER_EXPORT
	virtual ~SocketHandle();

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
	virtual void onRecv(NetworkSession *session, void *data, uint32_t data_len);

	BABELTRADER_EXPORT
	virtual void onSend(NetworkSession *session, void *data, uint32_t data_len);

	BABELTRADER_EXPORT
	virtual void recv(NetworkSession *session);

	BABELTRADER_EXPORT
	virtual void send(NetworkSession *session, void *data, uint32_t data_len);

	BABELTRADER_EXPORT
	void appendCodec(Codec *codec);

protected:
	CodecChain codec_chain_;
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_SOCKET_HANDLE_H_ */
