#include "example_tcp_server_config.h"

ExampleServerConfig::ExampleServerConfig()
	: JsonConfig()
{}
ExampleServerConfig::~ExampleServerConfig()
{}

bool ExampleServerConfig::onLoad(void *json_doc)
{
	// load tcp server config
	if (!tcp_server.onLoad(json_doc))
	{
		LOG_ERROR("failed load 'tcp_server' config");
		return false;
	}

	// load event loop config
	if (!ev_loop.onLoad(json_doc))
	{
		LOG_ERROR("failed load 'ev_loop' config");
		return false;
	}

	return true;
}
