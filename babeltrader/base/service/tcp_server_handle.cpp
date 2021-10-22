#include "tcp_server_handle.h"
#include "babeltrader/base/defines/enum.h"
#include "babeltrader/include/common_msg_type.h"
#include "babeltrader/include/common_net_message.h"
#include "babeltrader/include/common_msg_struct.h"

NS_BABELTRADER_BEGIN

TCPServerHandle::TCPServerHandle()
	: SocketHandle()
	, session_pool_(nullptr)
	, msg_pool_(nullptr)
	, event_loop_(nullptr)
	, bytes_buf_size_(BABELTRADER_DEFAULT_BYTES_BUF_SIZE)
	, recv_unit_size_(BABELTRADER_DEFAULT_RECV_UNIT_SIZE)
	, max_msg_size_(BABELTRADER_NET_MTU)
{}

TCPServerHandle::~TCPServerHandle()
{}

void TCPServerHandle::onListen(muggle_socket_event_t *, muggle::SocketPeer *peer)
{
	char buf[MUGGLE_SOCKET_ADDR_STRLEN];
	struct sockaddr *addr = (struct sockaddr*)&peer->getPeer()->addr;
	if (muggle_socket_ntop(
		addr, buf, MUGGLE_SOCKET_ADDR_STRLEN, 0) == NULL)
	{
		snprintf(buf, MUGGLE_SOCKET_ADDR_STRLEN, "unknown:unknown");
	}

	LOG_INFO("success listen: addr=%s", buf);
}

void TCPServerHandle::onConnect(muggle_socket_event_t *, muggle::SocketPeer *peer)
{
	TCPSession *session = newSession(peer);
	if (session == nullptr)
	{
		LOG_ERROR("failed newSession");
		return;
	}
	session->handle = this;

	LOG_INFO("TCP connection: remote_addr=%s", session->remote_addr);

	EventMessage *event_msg =
		(EventMessage*)msg_pool_->Allocate(BABELTRADER_EV_MSG_SIZE(MsgEmpty));
	if (event_msg == nullptr)
	{
		peer->close();
		LOG_ERROR("failed allocate connection event message: remote_addr=%s",
			session->remote_addr);
		return;
	}

	peer->retain();

	event_msg->msg_type = MSG_TYPE_TCP_CONNECT;
	event_msg->session = session;
	event_loop_->push(event_msg);
}

void TCPServerHandle::onMessage(muggle_socket_event_t*, muggle::SocketPeer *peer)
{
	TCPSession *session = (TCPSession*)peer->getUserData();
	recv((NetworkSession*)session);
}

void TCPServerHandle::onError(muggle_socket_event_t *, muggle::SocketPeer *peer)
{
	TCPSession *session = (TCPSession*)peer->getUserData();
	LOG_INFO("TCP disconnection: remote_addr=%s", session->remote_addr);

	EventMessage *event_msg =
		(EventMessage*)msg_pool_->Allocate(BABELTRADER_EV_MSG_SIZE(MsgEmpty));
	if (event_msg == nullptr)
	{
		LOG_ERROR("failed allocate disconnection event message: remote_addr=%s",
			session->remote_addr);
		return;
	}

	event_msg->msg_type = MSG_TYPE_TCP_DISCONNECT;
	event_msg->session = session;
	event_loop_->push(event_msg);
}

void TCPServerHandle::onClose(muggle_socket_event_t*, muggle::SocketPeer *peer)
{
	TCPSession *session = (TCPSession*)peer->getUserData();
	if (session)
	{
		muggle_bytes_buffer_destroy(&session->bytes_buf);

		session_pool_->Recycle(session);
		peer->setUserData(nullptr);
	}
}

void TCPServerHandle::onTimer(muggle_socket_event_t *)
{}

void TCPServerHandle::onRecv(NetworkSession *session, void *data, uint32_t data_len)
{
	if (data == nullptr)
	{
		LOG_ERROR("onRecv get nullptr data");
		return;
	}

	NetworkMessage *head = (NetworkMessage*)data;

	LOG_INFO(
		"TCP server handle onRecv: "
		"remote=%s, msg_type=%lu, data_len=%lu, payload_len=%lu",
		session->remote_addr, (unsigned long)head->msg_type,
		(unsigned long)data_len, (unsigned long)head->payload_len);

	EventMessage *event_msg =
		(EventMessage*)msg_pool_->Allocate(sizeof(EventMessage) + head->payload_len);
	if (event_msg == nullptr)
	{
		LOG_ERROR("failed allocate event message: remote_addr=%s",
			session->remote_addr);
		return;
	}

	event_msg->msg_type = head->msg_type;
	event_msg->session = session;

	void *dst_msg = (void*)(event_msg + 1);
	void *src_msg = (void*)(head + 1);
	memcpy(dst_msg, src_msg, (size_t)head->payload_len);

	event_loop_->push(event_msg);
}

void TCPServerHandle::onSend(NetworkSession *session, void *data, uint32_t data_len)
{
	muggle::SocketPeer *peer = session->peer;
	if (peer)
	{
		peer->send(data, data_len, 0);
	}
}

void TCPServerHandle::recv(NetworkSession *session)
{
	codec_chain_.decode(session, nullptr, 0);
}

void TCPServerHandle::send(NetworkSession *session, void *data, uint32_t data_len)
{
	codec_chain_.encode(session, data, data_len);
}

void TCPServerHandle::setSessionPool(muggle::IMemoryPool<TCPSession> *pool)
{
	session_pool_ = pool;
}

void TCPServerHandle::setEventMessagePool(EventMessagePool *pool)
{
	msg_pool_ = pool;
}

void TCPServerHandle::setEventLoop(EventLoop *event_loop)
{
	event_loop_ = event_loop;
}

void TCPServerHandle::setBytesBufferSize(uint32_t bytes_buf_size)
{
	bytes_buf_size_ = bytes_buf_size;
	if (bytes_buf_size < 1024)
	{
		bytes_buf_size_ = 1024;
	}
}

void TCPServerHandle::setRecvUnitSize(uint32_t recv_unit_size)
{
	recv_unit_size_ = recv_unit_size;
	if (recv_unit_size_ < 128)
	{
		recv_unit_size_ = 128;
	}
}

void TCPServerHandle::setMaxMsgSize(uint32_t max_msg_size)
{
	max_msg_size_ = max_msg_size;
}

TCPSession* TCPServerHandle::newSession(muggle::SocketPeer *peer)
{
	TCPSession *session = (TCPSession*)session_pool_->Allocate();
	if (session == nullptr)
	{
		peer->close();
		LOG_ERROR("failed allocate memory space for new TCP connection");
		return nullptr;
	}

	memset(session, 0, sizeof(*session));

	if (!muggle_bytes_buffer_init(&session->bytes_buf, bytes_buf_size_))
	{
		LOG_ERROR("failed init bytes buffer for new TCP connection");
		session_pool_->Recycle(session);
		return nullptr;
	}

	session->session_id = session_mgr_.newSessionId();

	if (muggle_socket_ntop(
			(struct sockaddr*)&peer->getPeer()->addr,
			session->remote_addr, MUGGLE_SOCKET_ADDR_STRLEN, 0) == NULL)
	{
		snprintf(session->remote_addr, MUGGLE_SOCKET_ADDR_STRLEN, "unknown:unknown");
	}

	session->recv_unit_size = recv_unit_size_;
	session->max_msg_size = max_msg_size_;

	peer->setUserData(session);
	session->peer = peer;

	return session;
}

NS_BABELTRADER_END
