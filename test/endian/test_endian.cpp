#include "gtest/gtest.h"
#include "test_utils/test_utils.h"
#include "babeltrader/api/cpp/internal/api_net_msg.h"

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
