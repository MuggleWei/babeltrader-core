#ifndef EXAMPLE_TCP_SERVER_CONFIG_H_
#define EXAMPLE_TCP_SERVER_CONFIG_H_

#include "babeltrader/utils/babeltrader_utils.h"

USING_NS_BABELTRADER;

class ExampleServerConfig : public JsonConfig
{
public:
	ExampleServerConfig();
	virtual ~ExampleServerConfig();

	virtual bool onLoad(void *json_doc) override;

public:
	TcpServerConfig tcp_server;
	EventLoopConfig ev_loop;
};

#endif /* ifndef EXAMPLE_TCP_SERVER_CONFIG_H_ */
