#include "endian_conv.h"

NS_BABELTRADER_BEGIN

EndianConv::EndianConv()
	: endian_(muggle_endianness())
	, net_endian_(MUGGLE_LITTLE_ENDIAN)
{}

EndianConv::~EndianConv()
{}

void EndianConv::setNetEndian(int net_endian)
{
	net_endian_ = net_endian;
}

bool EndianConv::needSwap()
{
	return endian_ != net_endian_;
}

void EndianConv::swapEndian(NetworkMessage &head)
{
	head.msg_type = swap(head.msg_type);
	head.payload_len = swap(head.payload_len);
}

void EndianConv::swapEndian(NetworkMsgHeartbeatPing &msg)
{
	swapEndian(msg.head);
	swapEndian(msg.msg);
}

void EndianConv::swapEndian(NetworkMsgHeartbeatPong &msg)
{
	swapEndian(msg.head);
	swapEndian(msg.msg);
}

void EndianConv::swapEndian(NetMsgReqQuoteSub &msg)
{
	swapEndian(msg.head);
	swapEndian(msg.msg);
}

void EndianConv::swapEndian(NetMsgRspQuoteSub &msg)
{
	swapEndian(msg.head);
	swapEndian(msg.msg);
}

int16_t EndianConv::swap(int16_t i16)
{
	return MUGGLE_ENDIAN_SWAP_16(i16);
}

uint16_t EndianConv::swap(uint16_t u16)
{
	return MUGGLE_ENDIAN_SWAP_16(u16);
}

int32_t EndianConv::swap(int32_t i32)
{
	return MUGGLE_ENDIAN_SWAP_32(i32);
}

uint32_t EndianConv::swap(uint32_t u32)
{
	return MUGGLE_ENDIAN_SWAP_32(u32);
}

int64_t EndianConv::swap(int64_t i64)
{
	return MUGGLE_ENDIAN_SWAP_64(i64);
}

uint64_t EndianConv::swap(uint64_t u64)
{
	return MUGGLE_ENDIAN_SWAP_64(u64);
}

void EndianConv::swapEndian(Instrument &msg)
{
	msg.api = swap(msg.api);
	msg.exchange = swap(msg.exchange);
}

void EndianConv::swapEndian(MsgErrorInfo &msg)
{
	msg.err_id = swap(msg.err_id);
	msg.uperr_id = swap(msg.uperr_id);
}

void EndianConv::swapEndian(MsgHeartbeatPing &msg)
{
	msg.sec = swap(msg.sec);
}

void EndianConv::swapEndian(MsgHeartbeatPong &msg)
{
	msg.sec = swap(msg.sec);
}

void EndianConv::swapEndian(MsgReqQuoteSub &msg)
{
	msg.req_id = swap(msg.req_id);
	msg.quote_type = swap(msg.quote_type);
	swapEndian(msg.instrument);
}

void EndianConv::swapEndian(MsgRspQuoteSub &msg)
{
	swapEndian(msg.req);
	swapEndian(msg.err_info);
}

NS_BABELTRADER_END
