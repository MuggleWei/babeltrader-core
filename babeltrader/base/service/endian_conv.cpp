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
NS_BABELTRADER_END
