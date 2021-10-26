#ifndef EXAMPLE_MSG_H_
#define EXAMPLE_MSG_H_

#include "babeltrader/include/common_msg_type.h"
#include "babeltrader/include/common_net_message.h"
#include <stdint.h>

enum
{
	EXAMPLE_MSG_FOO = babeltrader::MSG_TYPE_UPSTREAM_API_BEGIN + 1,
	EXAMPLE_MSG_BAR,
	MAX_EXAMPLE_MSG,
};

; // for avoid pragma warning tip in vim
#pragma pack(push, 1)

////////////// message struct //////////////
struct MessageFoo
{
	int64_t i64;
	char    s[32];
};

struct MessageBar
{
	char   s[32];
	float  f;
	double d;
};

////////////// network struct //////////////
struct NetMessageFoo
{
	babeltrader::NetworkMessage head;
	MessageFoo                  msg;
};

struct NetMessageBar
{
	babeltrader::NetworkMessage head;
	MessageBar                  msg;
};

#pragma pack(pop)

#endif /* ifndef EXAMPLE_MSG_H_ */
