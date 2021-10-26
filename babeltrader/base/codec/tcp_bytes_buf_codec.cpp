#include "tcp_bytes_buf_codec.h"
#include "babeltrader/base/log/log.h"
#include "babeltrader/include/common_net_message.h"

NS_BABELTRADER_BEGIN

TcpBytesBufCodec::TcpBytesBufCodec()
	: Codec()
{}

TcpBytesBufCodec::~TcpBytesBufCodec()
{}

bool TcpBytesBufCodec::encode(
	NetworkSession *session,
	void *data,
	uint32_t data_len)
{
	return Codec::encode(session, data, data_len);
}

bool TcpBytesBufCodec::decode(
	NetworkSession *session,
	void*,
	uint32_t)
{
	TCPSession *tcp_session = (TCPSession*)session;
	muggle::SocketPeer *peer = session->peer;
	muggle_bytes_buffer_t *bytes_buf = &tcp_session->bytes_buf;

	// read bytes into bytes buffer
	while (1)
	{
		void *p = muggle_bytes_buffer_writer_fc(bytes_buf, tcp_session->recv_unit_size);
		if (p == NULL)
		{
			MUGGLE_LOG_WARNING("bytes buffer full: %s", tcp_session->remote_addr);
			break;
		}

		int n = peer->recv(p, tcp_session->recv_unit_size, 0);
		if (n > 0)
		{
			muggle_bytes_buffer_writer_move(bytes_buf, n);
		}

		if (n < (int)tcp_session->recv_unit_size)
		{
			break;
		}
	}

	// parse network message
	NetworkMessage msg_head;
	while (1)
	{
		if (!muggle_bytes_buffer_fetch(bytes_buf, (int)sizeof(msg_head), &msg_head))
		{
			// readable bytes less than sizeof message head
			break;
		}

		// check payload length
		if (msg_head.payload_len > tcp_session->max_msg_size && tcp_session->max_msg_size != 0)
		{
			LOG_ERROR(
				"invalid payload length: remote_addr=%s, msg_type=%lu, payload_len=%lu",
				tcp_session->remote_addr,
				(unsigned long)msg_head.msg_type,
				(unsigned long)msg_head.payload_len);
			return false;
		}

		// check readable
		uint32_t total_bytes = (uint32_t)sizeof(NetworkMessage) + msg_head.payload_len;
		int readable = muggle_bytes_buffer_readable(bytes_buf);
		if ((uint32_t)readable < total_bytes)
		{
			break;
		}

		// get message pointer
		NetworkMessage *p_head =
			(NetworkMessage*)muggle_bytes_buffer_reader_fc(bytes_buf, (uint32_t)total_bytes);
		if (p_head)
		{
			bool ret = Codec::decode(session, p_head, total_bytes);

			muggle_bytes_buffer_reader_move(bytes_buf, (int)total_bytes);

			if (!ret)
			{
				return false;
			}
		}
		else
		{
			void *buf = malloc(total_bytes);
			muggle_bytes_buffer_read(bytes_buf, (int)total_bytes, buf);

			bool ret = Codec::decode(session, (NetworkMessage*)buf, total_bytes);

			free(buf);

			if (!ret)
			{
				return false;
			}
		}
	}

	return true;
}

NS_BABELTRADER_END
