#ifndef EXAMPLE_TCP_CLIENT_EV_LOOP_H_
#define EXAMPLE_TCP_CLIENT_EV_LOOP_H_

#include "babeltrader/base/babeltrader_base.h"
#include "example/include/example_msg.h"

USING_NS_BABELTRADER;

class ExampleClientEventLoop : public ServerEventLoop
{
public:
	ExampleClientEventLoop(int max_msg_type, int capacity, int flags);
	virtual ~ExampleClientEventLoop();

	virtual void registerCallbacks() override;

	virtual void onTCPConnect(EventMessage *msg, void *data) override;
	virtual void onTimer(EventMessage *msg, void *data) override;

	virtual void onMessageBar(EventMessage *msg, MessageBar *data);

private:
	int64_t req_id_;
};

#endif /* ifndef EXAMPLE_TCP_CLIENT_EV_LOOP_H_ */
