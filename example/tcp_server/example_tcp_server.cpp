#include <thread>
#include "babeltrader/base/babeltrader_base.h"
#include "example/include/example_msg.h"

void runTCPServer(babeltrader::EventLoop *ev_loop)
{
	std::thread th([ev_loop]{
		// configs
		unsigned int max_connect = 512;
		int chan_size = 1024;
		int socket_bytes_buf_size = 4096 * 1024;
		int socket_recv_unit_size = 4096;

		const char *host = "127.0.0.1";
		const char *serv = "10102";

		// TCP server handle
		muggle::MemoryPool<babeltrader::TCPSession> session_pool(max_connect);
		babeltrader::EventMsgSowrPool msg_pool(chan_size);
		babeltrader::TcpBytesBufCodec codec;

		babeltrader::TCPServerHandle handle;
		handle.setEventLoop(ev_loop);
		handle.appendCodec(&codec);
		handle.setEventMessagePool(&msg_pool);
		handle.setBytesBufferSize(socket_bytes_buf_size);
		handle.setRecvUnitSize(socket_recv_unit_size);
		handle.setMaxMsgSize(MAX_EXAMPLE_MSG);

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
	// initialize log
	if (!babeltrader::Log::Init(LOG_LEVEL_INFO, "log/example_tcp_server.log", LOG_LEVEL_DEBUG))
	{
		exit(EXIT_FAILURE);
	}

	LOG_INFO("Launch example TCP Server");

	// event loop
	int msg_pool_size = 1024;
	babeltrader::MessageDispatcher msg_dispatcher(MAX_EXAMPLE_MSG);
	babeltrader::EventLoop ev_loop(msg_pool_size, 0);
	ev_loop.setDispatcher(&msg_dispatcher);

	// run TCP server
	runTCPServer(&ev_loop);

	// run event loop
	ev_loop.run();

	return 0;
}
