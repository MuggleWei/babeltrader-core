#include "babeltrader/base/babeltrader_base.h"
#include "test_utils/test_utils.h"

USING_NS_BABELTRADER;

; // for avoid pragma warning tip in vim
#pragma pack(push, 1)

struct NetworkMsgDemo
{
	NetworkMessage head; //!< network message head

	uint32_t u32;
	int32_t  i32;
	float    f;
	double   d;
};
static_assert(sizeof(NetworkMsgDemo) < sizeof(NetworkMsgBlock), "");

#pragma pack(pop)

#define MSG_TYPE_DEMO 5

class ExampleCodec
{
public:
	void init()
	{
		initMockSocket(peer_, session_);
		initCodec();
	}

	void destroy()
	{
		muggle_bytes_buffer_destroy(&session_.bytes_buf);
	}

	void initMockSocket(MockTCPSocket &peer, TCPSession &session)
	{
		memset(&session, 0, sizeof(session));
		session.peer = &peer;
		strncpy(session.remote_addr, "unknown:unknown", sizeof(session.remote_addr) - 1);

		muggle_bytes_buffer_init(&session.bytes_buf, BABELTRADER_DEFAULT_BYTES_BUF_SIZE);
		session.recv_unit_size = BABELTRADER_DEFAULT_RECV_UNIT_SIZE;
		session.max_msg_size = 0;
		peer.setUserData(&session);
	}

	void initCodec()
	{
		codec_chain_.appendCodec(&tcp_bytes_buf_codec_);
		codec_chain_.setEncodeCallback(std::bind(
			&ExampleCodec::encodeCallback, this,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		codec_chain_.setDecodeCallback(std::bind(
			&ExampleCodec::decodeCallback, this,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	}

	bool encodeCallback(NetworkSession *session, void *data, uint32_t data_len)
	{
		NetworkMessage *msg = (NetworkMessage*)data;
		LOG_INFO(
			"encode callback: "
			"addr=%s, msg_type=%ld, payload_len=%ld, data_len=%ld",
			session->remote_addr,
			(unsigned long)msg->msg_type,
			(unsigned long)msg->payload_len,
			(unsigned long)data_len);
		// std::string hex_str = TestUtils::DumpBytesToHex(data, data_len);
		// LOG_INFO("bytes:\n%s", hex_str.c_str());
		return true;
	}

	bool decodeCallback(NetworkSession *session, void *data, uint32_t data_len)
	{
		NetworkMessage *msg = (NetworkMessage*)data;
		LOG_INFO(
			"decode callback: "
			"addr=%s, msg_type=%ld, payload_len=%ld, data_len=%ld",
			session->remote_addr,
			(unsigned long)msg->msg_type,
			(unsigned long)msg->payload_len,
			(unsigned long)data_len);
		// std::string hex_str = TestUtils::DumpBytesToHex(data, data_len);
		// LOG_INFO("bytes:\n%s", hex_str.c_str());

		switch (msg->msg_type)
		{
			case MSG_TYPE_DEMO:
			{
				onDemoMessage(session, (NetworkMsgDemo*)data);
			}break;
			default:
			{
				LOG_WARNING("on unrecongnized message: addr=%s, msg_type=%ld, payload_len=%ld",
					session->remote_addr,
					(unsigned long)msg->msg_type,
					(unsigned long)msg->payload_len);
			}break;
		}

		return true;
	}

	void onDemoMessage(NetworkSession *session, NetworkMsgDemo *msg)
	{
		LOG_INFO("on demo message: addr=%s, u32=%ld, i32=%ld, f=%f, d=%f",
			session->remote_addr, msg->u32, msg->i32, msg->f, msg->d);
	}

	template<typename T>
	bool writeMessage(T &msg)
	{
		return codec_chain_.encode((NetworkSession*)&session_, &msg, sizeof(msg));
	}

	void writeToSocketRecvRing(void *data, uint32_t data_len)
	{
		peer_.writeToReadRing(data, data_len);
	}

	bool onRecv()
	{
		return codec_chain_.decode((NetworkSession*)&session_, nullptr, 0);
	}

private:
	MockTCPSocket peer_;
	TCPSession session_;

	CodecChain codec_chain_;
	TcpBytesBufCodec tcp_bytes_buf_codec_;
};

void runExampleEncode(ExampleCodec &handle)
{
	NetworkMsgDemo msg;
	memset(&msg, 0, sizeof(msg));
	msg.head.msg_type = 5;
	msg.head.payload_len = BABELTRADER_NET_PAYLOAD_SIZE(NetworkMsgDemo);
	msg.u32 = 10;
	msg.i32 = -10;
	msg.f = 0.1;
	msg.d = -0.1;

	handle.writeMessage(msg);
}

void runExampleDecode(ExampleCodec &handle)
{
	NetworkMsgDemo msg_array[5];
	for (size_t i = 0; i < sizeof(msg_array)/sizeof(msg_array[0]); i++)
	{
		NetworkMsgDemo &msg = msg_array[i];
		memset(&msg, 0, sizeof(msg));
		msg.head.msg_type = MSG_TYPE_DEMO;
		msg.head.payload_len = BABELTRADER_NET_PAYLOAD_SIZE(NetworkMsgDemo);
		msg.u32 = i;
		msg.i32 = -1 * (int)i;
		msg.f = 0.1 * i;
		msg.d = -0.1 * i;
	}

	char *p = (char*)msg_array;
	int offset = 0;
	int step = 37;
	while (offset < (int)sizeof(msg_array))
	{
		if (offset + step > (int)sizeof(msg_array))
		{
			step = sizeof(msg_array) - offset;
		}

		LOG_INFO("write bytes to mock socket recv ring: offset=%d, step=%d",
			offset, step);

		handle.writeToSocketRecvRing(p + offset, step);

		offset += step;

		handle.onRecv();
	}
}

int main()
{
	// initialize log, console only
	babeltrader::Log::Init(LOG_LEVEL_INFO, NULL, 0);

	ExampleCodec handle;
	handle.init();

	// encode
	runExampleEncode(handle);

	// decode
	runExampleDecode(handle);

	handle.destroy();

	return 0;
}
