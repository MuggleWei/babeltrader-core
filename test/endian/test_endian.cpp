#include "gtest/gtest.h"
#include "babeltrader/base/babeltrader_base.h"
#include "test_utils/test_utils.h"

USING_NS_BABELTRADER;

class TestEndianFixture : public ::testing::Test
{
public:
	void SetUp()
	{
		host_endian_ = muggle_endianness();
		swap_endian_ =
			host_endian_ == MUGGLE_LITTLE_ENDIAN ? MUGGLE_BIG_ENDIAN : MUGGLE_LITTLE_ENDIAN;
	}

protected:
	EndianConv conv_;
	int host_endian_;
	int swap_endian_;
};

#define TEST_MSG_ENDIAN \
{ \
	conv_.setNetEndian(host_endian_); \
	BABELTRADER_SWAP_ENDIAN(conv_, msg_cpy); \
	ASSERT_TRUE(memcmp(&msg, &msg_cpy, sizeof(msg)) == 0); \
 \
	conv_.setNetEndian(swap_endian_); \
	BABELTRADER_SWAP_ENDIAN(conv_, msg_cpy); \
	ASSERT_TRUE(memcmp(&msg, &msg_cpy, sizeof(msg)) != 0); \
 \
	BABELTRADER_SWAP_ENDIAN(conv_, msg_cpy); \
	ASSERT_TRUE(memcmp(&msg, &msg_cpy, sizeof(msg)) == 0); \
}

TEST_F(TestEndianFixture, NetworkMessage)
{
	NetworkMessage msg;
	memset(&msg, 0, sizeof(msg));

	msg.msg_type = 1;
	msg.payload_len = 64;

	NetworkMessage msg_cpy;
	memcpy(&msg_cpy, &msg, sizeof(msg));

	TEST_MSG_ENDIAN;
}

TEST_F(TestEndianFixture, NetworkMsgHeartbeatPing)
{
	NetworkMsgHeartbeatPing msg;
	memset(&msg, 0, sizeof(msg));

	msg.head.msg_type = MSG_TYPE_HEARTBEAT_PING;
	msg.head.payload_len = sizeof(msg.msg);
	msg.msg.sec = (uint64_t)time(nullptr);

	NetworkMsgHeartbeatPing msg_cpy;
	memcpy(&msg_cpy, &msg, sizeof(msg));

	TEST_MSG_ENDIAN;
}

TEST_F(TestEndianFixture, NetworkMsgHeartbeatPong)
{
	NetworkMsgHeartbeatPong msg;
	memset(&msg, 0, sizeof(msg));

	msg.head.msg_type = MSG_TYPE_HEARTBEAT_PONG;
	msg.head.payload_len = sizeof(msg.msg);
	msg.msg.sec = (uint64_t)time(nullptr);

	NetworkMsgHeartbeatPong msg_cpy;
	memcpy(&msg_cpy, &msg, sizeof(msg));

	TEST_MSG_ENDIAN;
}

TEST_F(TestEndianFixture, NetMsgReqQuoteSub)
{
	NetMsgReqQuoteSub msg;
	memset(&msg, 0, sizeof(msg));

	msg.head.msg_type = MSG_TYPE_API_QUOTES_REQ_SUB;
	msg.head.payload_len = sizeof(msg.msg);

	msg.msg.req_id = 1;
	msg.msg.quote_type = EnumQuoteType::QUOTE_TYPE_SNAPSHOT;

	Instrument &instrument = msg.msg.instrument;
	instrument.api = EnumApi::API_CTP;
	instrument.exchange = EnumExchange::EXCHANGE_SHFE;
	instrument.product_type = EnumProductType::PRODUCT_TYPE_FUTURES;
	strncpy(instrument.instrument_id, "rb2201", sizeof(instrument.instrument_id));

	NetMsgReqQuoteSub msg_cpy;
	memcpy(&msg_cpy, &msg, sizeof(msg));

	TEST_MSG_ENDIAN;
}

TEST_F(TestEndianFixture, NetMsgRspQuoteSub)
{
	NetMsgRspQuoteSub msg;
	memset(&msg, 0, sizeof(msg));

	msg.head.msg_type = MSG_TYPE_API_QUOTES_REQ_SUB;
	msg.head.payload_len = sizeof(msg.msg);

	MsgReqQuoteSub &req = msg.msg.req;
	req.req_id = 1;
	req.quote_type = EnumQuoteType::QUOTE_TYPE_SNAPSHOT;

	Instrument &instrument = req.instrument;
	instrument.api = EnumApi::API_CTP;
	instrument.exchange = EnumExchange::EXCHANGE_SHFE;
	instrument.product_type = EnumProductType::PRODUCT_TYPE_FUTURES;
	strncpy(instrument.instrument_id, "rb2201", sizeof(instrument.instrument_id));

	msg.msg.err_info.err_id = 10001;

	NetMsgRspQuoteSub msg_cpy;
	memcpy(&msg_cpy, &msg, sizeof(msg));

	TEST_MSG_ENDIAN;
}
