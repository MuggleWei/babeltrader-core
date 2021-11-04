#include <thread>
#include "babeltrader/base/babeltrader_base.h"
#include "example/include/example_msg.h"
#include "example_tcp_client_ev_loop.h"

void runTCPClient(babeltrader::EventLoop *ev_loop)
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

		// TCP client handle
		muggle::MemoryPool<babeltrader::TCPSession> session_pool(max_connect);
		babeltrader::EventMsgSowrPool msg_pool(chan_size);
		babeltrader::TcpBytesBufCodec codec;

		babeltrader::TCPSocketHandle handle;
		handle.setEventLoop(ev_loop);
		handle.appendCodec(&codec);
		handle.setSessionPool(&session_pool);
		handle.setEventMessagePool(&msg_pool);
		handle.setBytesBufferSize(socket_bytes_buf_size);
		handle.setRecvUnitSize(socket_recv_unit_size);
		handle.setMaxMsgSize(max_msg_size);
		handle.setConnRole(babeltrader::CONNECT_ROLE_SERVER);
		handle.setConnHandleId(0);

		muggle::TcpClient tcp_client;
		tcp_client.setHandle(&handle);
		tcp_client.setConnectAddr(host, serv);
		tcp_client.setTcpNoDelay(true);
		// tcp_client.setTimer(3000);
		tcp_client.setAutoReconnect(true, 3000);
		tcp_client.setConnectTimeout(3);
		tcp_client.run();
	});
	th.detach();
}

int main()
{
	// init log
	if (!babeltrader::Log::Init(LOG_LEVEL_INFO, "log/example_tcp_client.log", LOG_LEVEL_DEBUG))
	{
		exit(EXIT_FAILURE);
	}

	// init socket
	muggle_socket_lib_init();

	LOG_INFO("Launch example TCP Client");

	// event loop
	int timer_interval_ms = 10;
	int idle_timeout = 0;
	int chan_size = BABELTRADER_DEFAULT_PIPE_SIZE;
	ExampleClientEventLoop ev_loop(MAX_EXAMPLE_MSG, chan_size, 0);
	ev_loop.setTimerMs(timer_interval_ms);
	ev_loop.setIdleTimeout(idle_timeout);

	// run TCP server
	runTCPClient(&ev_loop);

	// run event loop
	ev_loop.run();

	return 0;
}

