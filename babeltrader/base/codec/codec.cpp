#include "codec.h"
#include "babeltrader/base/log/log.h"

NS_BABELTRADER_BEGIN

Codec::Codec()
	: next_(nullptr)
	, prev_(nullptr)
{}

Codec::~Codec()
{}

bool Codec::encode(
	NetworkSession *session,
	void *data,
	uint32_t data_len)
{
	bool ret = false;
	if (next_)
	{
		ret = next_->encode(session, data, data_len);
	}

	return ret;
}

bool Codec::decode(
	NetworkSession *session,
	void *data,
	uint32_t data_len)
{
	bool ret = false;
	if (prev_)
	{
		ret = prev_->decode(session, data, data_len);
	}

	return ret;
}

Codec* Codec::getNext()
{
	return next_;
}

Codec* Codec::getPrev()
{
	return prev_;
}

void Codec::append(Codec *codec)
{
	next_ = codec;
	codec->prev_ = this;
}
NS_BABELTRADER_END
