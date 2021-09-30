/******************************************************************************
 *  @file         mock_tcp_socket.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-26
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader mock TCP socket
 *****************************************************************************/

#include "test_utils/mock/mock_socket.h"

NS_BABELTRADER_BEGIN

class MockTCPSocket : public MockSocket
{
public:
	TESTUTILS_EXPORT
	MockTCPSocket();

	TESTUTILS_EXPORT
	virtual ~MockTCPSocket();

	TESTUTILS_EXPORT
	virtual void writeToReadRing(void *data, uint32_t len) override;

	TESTUTILS_EXPORT
	virtual void readFromWriteRing(void *buf, uint32_t *len) override;

	TESTUTILS_EXPORT
	virtual int recv(void *buf, size_t len, int flags) override;

	TESTUTILS_EXPORT
	virtual int recvFrom(
		void *buf, size_t len, int flags,
		struct sockaddr *addr, muggle_socklen_t *addrlen) override;

	TESTUTILS_EXPORT
	virtual int send(const void *buf, size_t len, int flags) override;

	TESTUTILS_EXPORT
	virtual int sendTo(
		const void *buf, size_t len, int flags,
		const struct sockaddr *dst_addr, muggle_socklen_t addrlen) override;

private:
	muggle_bytes_buffer_t read_ring_;
	muggle_bytes_buffer_t write_ring_;
};

NS_BABELTRADER_END
