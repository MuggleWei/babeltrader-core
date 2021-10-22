#ifndef EXAMPLE_TCP_SERVER_EV_LOOP_H_
#define EXAMPLE_TCP_SERVER_EV_LOOP_H_

#include "babeltrader/base/babeltrader_base.h"
#include "example/include/example_msg.h"

USING_NS_BABELTRADER;

class ExampleEventLoop : public ServerEventLoop
{
public:
	ExampleEventLoop(int max_msg_type, int capacity, int flags);
	virtual ~ExampleEventLoop();

	virtual void registerCallbacks();

	virtual void onTimer(EventMessage *msg, void *data);
	virtual void onMessageFoo(EventMessage *msg, MessageFoo *data);
	virtual void onMessageBar(EventMessage *msg, MessageBar *data);
};

#endif /* ifndef EXAMPLE_TCP_SERVER_EV_LOOP_H_ */
