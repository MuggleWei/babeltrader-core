/******************************************************************************
 *  @file         ev_loop_config.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-11-02
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader event loop config
 *****************************************************************************/

#ifndef BABELTRADER_EV_LOOP_CONFIG_H_
#define BABELTRADER_EV_LOOP_CONFIG_H_

#include "babeltrader/utils/utils_macro.h"
#include "babeltrader/utils/json_config.h"
#include <string>

NS_BABELTRADER_BEGIN

class EventLoopConfig : public JsonConfig
{
public:
	BABELTRADER_UTILS_EXPORT
	EventLoopConfig();

	BABELTRADER_UTILS_EXPORT
	virtual ~EventLoopConfig();

	BABELTRADER_UTILS_EXPORT
	virtual bool onLoad(void *json_doc) override;

public:
	int timer_interval_ms;
	int idle_timeout;
	int pipe_size;
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_EV_LOOP_CONFIG_H_ */
