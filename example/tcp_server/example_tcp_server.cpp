#include <thread>
#include "babeltrader/base/babeltrader_base.h"
#include "babeltrader/utils/babeltrader_utils.h"
#include "example/include/example_msg.h"
#include "example_tcp_server_config.h"
#include "example_tcp_server_ev_loop.h"

void runTCPServer(babeltrader::EventLoop *ev_loop, ExampleServerConfig *cfg)
{
	std::thread th([ev_loop, cfg]{
		// config
		ExampleServerConfig &config = *cfg;

		char serv[32];
		snprintf(serv, sizeof(serv), "%d", config.tcp_server.port);

		int max_msg_size = BABELTRADER_NET_MTU - sizeof(NetworkMessage);

		// TCP server handle
		muggle::MemoryPool<babeltrader::TCPSession> session_pool(config.tcp_server.hints_max_connect);
		babeltrader::EventMsgSowrPool msg_pool(config.tcp_server.msg_pool_size);
		babeltrader::TcpBytesBufCodec codec;

		babeltrader::TCPSocketHandle handle;
		handle.setEventLoop(ev_loop);
		handle.appendCodec(&codec);
		handle.setSessionPool(&session_pool);
		handle.setEventMessagePool(&msg_pool);
		handle.setBytesBufferSize(config.tcp_server.bytes_buf_size);
		handle.setRecvUnitSize(config.tcp_server.recv_unit_size);
		handle.setMaxMsgSize(max_msg_size);
		handle.setConnRole(babeltrader::CONNECT_ROLE_CLIENT);
		handle.setConnHandleId(0);

		// TCP server
		muggle::TcpServer tcp_server;
		tcp_server.setHandle(&handle);
		tcp_server.setListenAddr(config.tcp_server.host.c_str(), serv);
		tcp_server.setTcpNoDelay(true);
		tcp_server.setHintsMaxPeer(config.tcp_server.hints_max_connect);

		tcp_server.run();
	});
	th.detach();
}

void loadConfig(int argc, char *argv[], ExampleServerConfig &config)
{
	const char *cfg_file_path = "config/tcp_server.json";
	int opt;
	while ((opt = getopt(argc, argv, "c:")) != -1)
	{
		switch (opt)
		{
			case 'c':
			{
				cfg_file_path = optarg;
			}break;
		}
	}

	LOG_INFO("load config file: %s", cfg_file_path);
	if (!config.load(cfg_file_path))
	{
		LOG_ERROR("failed load config file: %s", cfg_file_path);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	// init log
	if (!babeltrader::Log::Init(LOG_LEVEL_INFO, "log/example_tcp_server.log", LOG_LEVEL_DEBUG))
	{
		exit(EXIT_FAILURE);
	}

	// init socket
	muggle_socket_lib_init();

	// load config
	ExampleServerConfig config;
	loadConfig(argc, argv, config);

	LOG_INFO("Launch example TCP Server");

	// event loop
	ExampleServerEventLoop ev_loop(MAX_EXAMPLE_MSG, config.ev_loop.pipe_size, 0);
	ev_loop.setTimerMs(config.ev_loop.timer_interval_ms);
	ev_loop.setIdleTimeout(config.ev_loop.idle_timeout);

	// run TCP server
	runTCPServer(&ev_loop, &config);

	// run event loop
	ev_loop.run();

	return 0;
}
