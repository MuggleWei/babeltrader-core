#include "codec_callback.h"

NS_BABELTRADER_BEGIN

CodecCallback::CodecCallback()
	: Codec()
{}

CodecCallback::~CodecCallback()
{}

bool CodecCallback::encode(
		NetworkSession *session,
		void *data,
		uint32_t data_len)
{
	if (!encode_cb_)
	{
		return false;
	}

	return encode_cb_(session, data, data_len);
}

bool CodecCallback::decode(
		NetworkSession *session,
		void *data,
		uint32_t data_len)
{
	if (!decode_cb_)
	{
		return false;
	}

	return decode_cb_(session, data, data_len);
}

void CodecCallback::setEncodeCallback(func_codec_cb &cb)
{
	encode_cb_ = cb;
}

void CodecCallback::setDecodeCallback(func_codec_cb &cb)
{
	decode_cb_ = cb;
}

NS_BABELTRADER_END
