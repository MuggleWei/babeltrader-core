#include "socket_handle.h"

NS_BABELTRADER_BEGIN

SocketHandle::SocketHandle()
	: muggle::SocketHandle()
{
	func_codec_cb encode_cb = [&](NetworkSession *session, void *data, uint32_t data_len) -> bool {
		this->onSend(session, data, data_len);
		return true;
	};
	codec_chain_.setEncodeCallback(encode_cb);

	func_codec_cb decode_cb = [&](NetworkSession *session, void *data, uint32_t data_len) -> bool {
		this->onRecv(session, data, data_len);
		return true;
	};
	codec_chain_.setDecodeCallback(decode_cb);
}

SocketHandle::~SocketHandle()
{}

void SocketHandle::onListen(muggle_socket_event_t*, muggle::SocketPeer*)
{}

void SocketHandle::onConnect(muggle_socket_event_t*, muggle::SocketPeer*)
{}

void SocketHandle::onMessage(muggle_socket_event_t*, muggle::SocketPeer*)
{}

void SocketHandle::onError(muggle_socket_event_t*, muggle::SocketPeer*)
{}

void SocketHandle::onClose(muggle_socket_event_t*, muggle::SocketPeer*)
{}

void SocketHandle::onTimer(muggle_socket_event_t*)
{}

void SocketHandle::onRecv(NetworkSession*, void*, uint32_t)
{}

void SocketHandle::onSend(NetworkSession*, void*, uint32_t)
{}

void SocketHandle::recv(NetworkSession*)
{}

void SocketHandle::send(NetworkSession*, void *, uint32_t)
{}

void SocketHandle::appendCodec(Codec *codec)
{
	codec_chain_.appendCodec(codec);
}

NS_BABELTRADER_END
