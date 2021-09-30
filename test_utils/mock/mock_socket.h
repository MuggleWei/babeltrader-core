/******************************************************************************
 *  @file         mock_socket.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-26
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader mock socket
 *****************************************************************************/

#ifndef BABELTRADER_TEST_UTILS_MOCK_SOCKET_H_
#define BABELTRADER_TEST_UTILS_MOCK_SOCKET_H_

#include "test_utils/test_utils_macro.h"

NS_BABELTRADER_BEGIN

class MockSocket : public muggle::SocketPeer
{
public:
	/**
	 * @brief mock socket constructor
	 */
	TESTUTILS_EXPORT
	MockSocket();

	/**
	 * @brief mock socket destructor
	 */
	TESTUTILS_EXPORT
	virtual ~MockSocket();

	/**
	 * @brief write data into socket read ring
	 *
	 * @param data  data pointer
	 * @param len   number bytes in data
	 */
	TESTUTILS_EXPORT
	virtual void writeToReadRing(void *data, uint32_t len);

	/**
	 * @brief read data from socket write ring
	 *
	 * @param buf  buffer store data that read from write ring
	 * @param len  buffer len and return number bytes of read
	 */
	TESTUTILS_EXPORT
	virtual void readFromWriteRing(void *buf, uint32_t *len);
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_TEST_UTILS_MOCK_SOCKET_H_ */
