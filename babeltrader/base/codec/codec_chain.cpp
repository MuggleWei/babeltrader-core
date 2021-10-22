#include "codec_chain.h"

NS_BABELTRADER_BEGIN

CodecChain::CodecChain()
	: encode_head_(&encode_cb_)
	, decode_head_(&decode_cb_)
{
	decode_cb_.append(&encode_cb_);
}

CodecChain::~CodecChain()
{}

bool CodecChain::encode(
	NetworkSession *session,
	void *data,
	uint32_t data_len)
{
	return encode_head_->encode(session, data, data_len);
}

bool CodecChain::decode(
	NetworkSession *session,
	void *data,
	uint32_t data_len)
{
	return decode_head_->decode(session, data, data_len);
}

void CodecChain::appendCodec(Codec *codec)
{
	Codec *prev = encode_cb_.getPrev();
	prev->append(codec);
	codec->append(&encode_cb_);

	encode_head_ = decode_cb_.getNext();
	decode_head_ = encode_cb_.getPrev();
}

void CodecChain::setEncodeCallback(const func_codec_cb &cb)
{
	encode_cb_.setEncodeCallback(cb);
}

void CodecChain::setDecodeCallback(const func_codec_cb &cb)
{
	decode_cb_.setDecodeCallback(cb);
}

NS_BABELTRADER_END
