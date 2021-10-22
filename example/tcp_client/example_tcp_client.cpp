#include "babeltrader/base/babeltrader_base.h"

int main()
{
	// init log
	if (!babeltrader::Log::Init(LOG_LEVEL_INFO, "log/example_tcp_client.log", LOG_LEVEL_TRACE))
	{
		exit(EXIT_FAILURE);
	}

	// init socket
	muggle_socket_lib_init();

	LOG_INFO("Launch example TCP Client");

	return 0;
}

