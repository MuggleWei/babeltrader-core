#include <thread>
#include "babeltrader/base/babeltrader_base.h"
#include "example/include/example_msg.h"
#include "example_tcp_server_ev_loop.h"

void runTCPServer(babeltrader::EventLoop *ev_loop)
{
	std::thread th([ev_loop]{
		// configs
		unsigned int max_connect = BABELTRADER_DEFAULT_HINTS_MAX_CONN;
		int chan_size = BABELTRADER_DEFAULT_PIPE_SIZE;
		int socket_bytes_buf_size = BABELTRADER_DEFAULT_BYTES_BUF_SIZE;
		int socket_recv_unit_size = BABELTRADER_DEFAULT_RECV_UNIT_SIZE;
		int max_msg_size = BABELTRADER_DEFAULT_RECV_UNIT_SIZE;

		const char *host = "127.0.0.1";
		const char *serv = "10102";

		// TCP server handle
		muggle::MemoryPool<babeltrader::TCPSession> session_pool(max_connect);
		babeltrader::EventMsgSowrPool msg_pool(chan_size);
		babeltrader::TcpBytesBufCodec codec;

		babeltrader::TCPServerHandle handle;
		handle.setEventLoop(ev_loop);
		handle.appendCodec(&codec);
		handle.setSessionPool(&session_pool);
		handle.setEventMessagePool(&msg_pool);
		handle.setBytesBufferSize(socket_bytes_buf_size);
		handle.setRecvUnitSize(socket_recv_unit_size);
		handle.setMaxMsgSize(max_msg_size);

		// TCP server
		muggle::TcpServer tcp_server;
		tcp_server.setHandle(&handle);
		tcp_server.setHintsMaxPeer(max_connect);
		tcp_server.setListenAddr(host, serv);
		tcp_server.setTcpNoDelay(true);

		tcp_server.run();
	});
	th.detach();
}

int main()
{
	// init log
	if (!babeltrader::Log::Init(LOG_LEVEL_INFO, "log/example_tcp_server.log", LOG_LEVEL_TRACE))
	{
		exit(EXIT_FAILURE);
	}

	// init socket
	muggle_socket_lib_init();

	LOG_INFO("Launch example TCP Server");

	// event loop
	int msg_pool_size = 1024;
	ExampleEventLoop ev_loop(MAX_EXAMPLE_MSG, msg_pool_size, 0);

	// run TCP server
	runTCPServer(&ev_loop);

	// run timer
	ev_loop.runTimer(3000);

	// run event loop
	ev_loop.run();

	return 0;
}
