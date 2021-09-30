#include "mock_socket.h"

NS_BABELTRADER_BEGIN

MockSocket::MockSocket()
	: muggle::SocketPeer()
{}

MockSocket::~MockSocket()
{}

void MockSocket::writeToReadRing(void*, uint32_t)
{}
void MockSocket::readFromWriteRing(void*, uint32_t*)
{}

NS_BABELTRADER_END
