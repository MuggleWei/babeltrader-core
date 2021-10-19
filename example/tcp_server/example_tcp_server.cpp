#include "babeltrader/base/babeltrader_base.h"

int main()
{
	// initialize log
	if (!babeltrader::Log::Init(LOG_LEVEL_INFO, "log/example_tcp_server.log", LOG_LEVEL_DEBUG))
	{
		exit(EXIT_FAILURE);
	}

	LOG_INFO("Launch example TCP Server");

	return 0;
}
