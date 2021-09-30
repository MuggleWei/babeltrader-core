#include "mock_tcp_socket.h"

NS_BABELTRADER_BEGIN

MockTCPSocket::MockTCPSocket()
	: MockSocket()
{
	muggle_bytes_buffer_init(&read_ring_, 1024 * 1024 * 8);
	muggle_bytes_buffer_init(&write_ring_, 1024 * 1024 * 8);
}

MockTCPSocket::~MockTCPSocket()
{
	muggle_bytes_buffer_destroy(&read_ring_);
	muggle_bytes_buffer_destroy(&write_ring_);
}

void MockTCPSocket::writeToReadRing(void *data, uint32_t len)
{
	muggle_bytes_buffer_write(&read_ring_, (int)len, data);
}

void MockTCPSocket::readFromWriteRing(void *buf, uint32_t *len)
{
	int readable = muggle_bytes_buffer_readable(&write_ring_);
	int num_bytes = readable > (int)*len ? (int)*len : readable;
	*len = num_bytes;
	muggle_bytes_buffer_read(&write_ring_, num_bytes, buf);
}

int MockTCPSocket::recv(void *buf, size_t len, int)
{
	int readable = muggle_bytes_buffer_readable(&read_ring_);
	int num_bytes = readable > (int)len ? (int)len : readable;

	muggle_bytes_buffer_read(&read_ring_, num_bytes, buf);

	return num_bytes;
}

int MockTCPSocket::recvFrom(
		void*, size_t, int,
		struct sockaddr*, muggle_socklen_t*)
{
	return -1;
}

int MockTCPSocket::send(const void *buf, size_t len, int)
{
	void *src = (void*)(intptr_t)buf;
	if (!muggle_bytes_buffer_write(&write_ring_, (int)len, src))
	{
		return -1;
	}
	return len;
}

int MockTCPSocket::sendTo(
		const void*, size_t, int,
		const struct sockaddr*, muggle_socklen_t)
{
	return -1;
}

NS_BABELTRADER_END
