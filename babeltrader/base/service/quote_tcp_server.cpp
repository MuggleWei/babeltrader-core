#include "quote_tcp_server.h"
#include "tcp_server_handle.h"
#include "babeltrader/base/codec/tcp_bytes_buf_codec.h"

NS_BABELTRADER_BEGIN

QuoteTcpServer::QuoteTcpServer()
	: quote_cfg_(nullptr)
	, ev_loop_(nullptr)
	, endian_codec_(nullptr)
{}

QuoteTcpServer::~QuoteTcpServer()
{}

void QuoteTcpServer::setQuoteConfig(QuoteServerConfig *cfg)
{
	quote_cfg_ = cfg;
}

void QuoteTcpServer::setEventLoop(EventLoop *ev_loop)
{
	ev_loop_ = ev_loop;
}

void QuoteTcpServer::setEndianCodec(Codec *codec)
{
	endian_codec_ = codec;
}

void QuoteTcpServer::run()
{
	// TCP server handle
	TCPServerHandle handle;

	muggle::MemoryPool<TCPSession> session_pool(quote_cfg_->hints_max_connect);
	EventMsgSowrPool message_pool(quote_cfg_->event_pipe_size);
	TcpBytesBufCodec codec;

	handle.setEventLoop(ev_loop_);
	if (endian_codec_)
	{
		handle.appendCodec(endian_codec_);
	}
	handle.appendCodec(&codec);
	handle.setSessionPool(&session_pool);
	handle.setEventMessagePool(&message_pool);
	handle.setBytesBufferSize(quote_cfg_->socket_bytes_buf_size);
	handle.setRecvUnitSize(quote_cfg_->recv_unit_size);
	handle.setMaxMsgSize(quote_cfg_->max_msg_size);

	// TCP server
	muggle::TcpServer tcp_server;

	const char *host = quote_cfg_->tcp_listen_ip.c_str();
	char port[64];
	snprintf(port, sizeof(port), "%d", quote_cfg_->tcp_listen_port);

	tcp_server.setHandle(&handle);
	tcp_server.setHintsMaxPeer(quote_cfg_->hints_max_connect);
	tcp_server.setListenAddr(host, port);
	tcp_server.setTcpNoDelay(true);

	tcp_server.run();
}

NS_BABELTRADER_END
