#ifndef EXAMPLE_TCP_SERVER_EV_LOOP_H_
#define EXAMPLE_TCP_SERVER_EV_LOOP_H_

#include "babeltrader/base/babeltrader_base.h"
#include "example/include/example_msg.h"

USING_NS_BABELTRADER;

class ExampleServerEventLoop : public ServerEventLoop
{
public:
	ExampleServerEventLoop(int max_msg_type, int capacity, int flags);
	virtual ~ExampleServerEventLoop();

	virtual void registerCallbacks();

	virtual void onTimer(EventMessage *msg, void *data);
	virtual void onMessageFoo(EventMessage *msg, MessageFoo *data);

private:
	int msg_cnt_;
};

#endif /* ifndef EXAMPLE_TCP_SERVER_EV_LOOP_H_ */
