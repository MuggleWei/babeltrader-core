#include "gtest/gtest.h"
#include <list>
#include <type_traits>
#include "test_utils/test_utils.h"

USING_NS_BABELTRADER;

struct NetworkMsgRet
{
	NetworkMsgBlock block;
	uint32_t data_len;
};

class TestTcpBytesBufCodecFixture : public ::testing::Test
{
public:
	void SetUp()
	{
		initSession();
		initCodec();
	}

	void TearDown()
	{
		muggle_bytes_buffer_destroy(&session_.bytes_buf);
	}

	void initSession()
	{
		static_assert(std::is_trivial<TCPSession>::value, "TCP Session must trivial type");

		memset(&session_, 0, sizeof(session_));
		session_.peer = &peer_;
		strncpy(session_.remote_addr, "unknown:unknown", sizeof(session_.remote_addr) - 1);

		muggle_bytes_buffer_init(&session_.bytes_buf, 1024 * 1024 * 8);
		session_.recv_unit_size = 4096;
		session_.max_msg_size = 0;
		session_.user_data = nullptr;

		peer_.setUserData(&session_);
	}

	void initCodec()
	{
		codec_chain_.appendCodec(&tcp_bytes_buf_codec_);

		func_codec_cb encode_cb = std::bind(
			&TestTcpBytesBufCodecFixture::encodeCallback, this,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		codec_chain_.setEncodeCallback(encode_cb);

		func_codec_cb decode_cb = std::bind(
			&TestTcpBytesBufCodecFixture::decodeCallback, this,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		codec_chain_.setDecodeCallback(decode_cb);
	}

	bool encodeCallback(NetworkSession*, void *data, uint32_t data_len)
	{
		if (data_len > sizeof(NetworkMsgBlock))
		{
			return false;
		}

		NetworkMsgRet ret;
		memcpy(&ret.block, data, data_len);
		ret.data_len = data_len;

		encode_ret_list_.push_back(ret);

		return true;
	}

	bool decodeCallback(NetworkSession*, void *data, uint32_t data_len)
	{
		if (data_len > sizeof(NetworkMsgBlock))
		{
			return false;
		}

		NetworkMsgRet ret;
		memcpy(&ret.block, data, data_len);
		ret.data_len = data_len;

		decode_ret_list_.push_back(ret);

		return true;
	}

protected:
	MockTCPSocket peer_;
	TCPSession session_;

	CodecChain codec_chain_;
	TcpBytesBufCodec tcp_bytes_buf_codec_;

	std::list<NetworkMsgRet> encode_ret_list_;
	std::list<NetworkMsgRet> decode_ret_list_;
};

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

TEST_F(TestTcpBytesBufCodecFixture, whole_packet)
{
	// fillup struct
	NetworkMsgDemo msg;
	memset(&msg, 0, sizeof(msg));
	msg.head.msg_type = 5;
	msg.head.payload_len = BABELTRADER_NET_PAYLOAD_SIZE(NetworkMsgDemo);
	msg.u32 = 10;
	msg.i32 = -10;
	msg.f = 0.1;
	msg.d = -0.1;

	// copy to network message
	NetworkMsgBlock block;
	NetworkMsgDemo *net_msg = (NetworkMsgDemo*)&block;
	memcpy(net_msg, &msg, sizeof(NetworkMsgDemo));

	bool ret = false;

	// encode
	ret = codec_chain_.encode(
		(NetworkSession*)&session_, net_msg, sizeof(NetworkMsgDemo));
	ASSERT_TRUE(ret);

	ASSERT_EQ(encode_ret_list_.size(), 1);
	NetworkMsgRet &encode_ret = encode_ret_list_.front();
	NetworkMsgDemo *encoded_msg = (NetworkMsgDemo*)&encode_ret.block;
	ASSERT_EQ(encode_ret.data_len, sizeof(NetworkMsgDemo));
	ASSERT_EQ(encoded_msg->head.msg_type, msg.head.msg_type);
	ASSERT_EQ(encoded_msg->head.payload_len, msg.head.payload_len);
	ASSERT_EQ(msg.u32, encoded_msg->u32);
	ASSERT_EQ(msg.i32, encoded_msg->i32);
	ASSERT_EQ(msg.f, encoded_msg->f);
	ASSERT_EQ(msg.d, encoded_msg->d);

	// decode
	peer_.writeToReadRing((void*)&encode_ret.block, encode_ret.data_len);

	ret = codec_chain_.decode(
		(NetworkSession*)&session_, nullptr, 0);
	ASSERT_TRUE(ret);

	ASSERT_EQ(decode_ret_list_.size(), 1);
	NetworkMsgRet &decode_ret = decode_ret_list_.front();
	NetworkMsgDemo *decoded_msg = (NetworkMsgDemo*)&decode_ret.block;
	ASSERT_EQ(decode_ret.data_len, sizeof(NetworkMsgDemo));
	ASSERT_EQ(decoded_msg->head.msg_type, msg.head.msg_type);
	ASSERT_EQ(decoded_msg->head.payload_len, msg.head.payload_len);
	ASSERT_EQ(msg.u32, decoded_msg->u32);
	ASSERT_EQ(msg.i32, decoded_msg->i32);
	ASSERT_EQ(msg.f, decoded_msg->f);
	ASSERT_EQ(msg.d, decoded_msg->d);
}

TEST_F(TestTcpBytesBufCodecFixture, sticky_packet)
{
	// fillup struct
	NetworkMsgDemo msg;
	memset(&msg, 0, sizeof(msg));
	msg.head.msg_type = 5;
	msg.head.payload_len = BABELTRADER_NET_PAYLOAD_SIZE(NetworkMsgDemo);
	msg.u32 = 10;
	msg.i32 = -10;
	msg.f = 0.1;
	msg.d = -0.1;

	// copy to network message
	NetworkMsgBlock block;
	NetworkMsgDemo *net_msg = (NetworkMsgDemo*)&block;
	memcpy(net_msg, &msg, sizeof(NetworkMsgDemo));

	bool ret = false;

	// encode
	ret = codec_chain_.encode(
		(NetworkSession*)&session_, net_msg, sizeof(NetworkMsgDemo));
	ASSERT_TRUE(ret);

	// sticky packet
	ASSERT_EQ(encode_ret_list_.size(), 1);
	NetworkMsgRet &encode_ret = encode_ret_list_.front();
	char *p = (char*)&encode_ret.block;
	for (uint32_t i = 0; i < encode_ret.data_len - 1; i++)
	{
		peer_.writeToReadRing(p+i, 1);
		ret = codec_chain_.decode(
			(NetworkSession*)&session_, nullptr, 0);
		ASSERT_TRUE(ret);
		ASSERT_EQ(decode_ret_list_.size(), 0);
	}

	peer_.writeToReadRing(p+encode_ret.data_len-1, 1);
	ret = codec_chain_.decode(
		(NetworkSession*)&session_, nullptr, 0);
	ASSERT_TRUE(ret);
	ASSERT_EQ(decode_ret_list_.size(), 1);
	NetworkMsgRet &decode_ret = decode_ret_list_.front();
	NetworkMsgDemo *decoded_msg = (NetworkMsgDemo*)&decode_ret.block;
	ASSERT_EQ(decode_ret.data_len, sizeof(NetworkMsgDemo));
	ASSERT_EQ(decoded_msg->head.msg_type, msg.head.msg_type);
	ASSERT_EQ(decoded_msg->head.payload_len, msg.head.payload_len);
	ASSERT_EQ(msg.u32, decoded_msg->u32);
	ASSERT_EQ(msg.i32, decoded_msg->i32);
	ASSERT_EQ(msg.f, decoded_msg->f);
	ASSERT_EQ(msg.d, decoded_msg->d);
}
