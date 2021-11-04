#include "ev_loop_config.h"

#include "babeltrader/base/defines/enum.h"
#include "babeltrader/utils/json_utils.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/error/en.h"

NS_BABELTRADER_BEGIN

EventLoopConfig::EventLoopConfig()
	: JsonConfig()
	, timer_interval_ms(BABELTRADER_DEFAULT_SERV_TIMER_INTERVAL)
	, idle_timeout(BABELTRADER_DEFAULT_SERV_IDLE)
	, pipe_size(BABELTRADER_DEFAULT_PIPE_SIZE)
{}

EventLoopConfig::~EventLoopConfig()
{}

bool EventLoopConfig::onLoad(void *json_doc)
{
	rapidjson::Document *p_root_doc = (rapidjson::Document*)json_doc;
	rapidjson::Document &root_doc = *p_root_doc;

	if (!BABELTRADER_JSON_HAS_OBJ(root_doc, "ev_loop"))
	{
		LOG_ERROR("can't find field 'ev_loop' with object type");
		return false;
	}
	rapidjson::Value &doc = root_doc["ev_loop"];

	BABELTRADER_JSON_GET_INT(timer_interval_ms, doc, "timer_interval_ms", BABELTRADER_DEFAULT_SERV_TIMER_INTERVAL);
	BABELTRADER_JSON_GET_INT(idle_timeout, doc, "idle_timeout", BABELTRADER_DEFAULT_SERV_IDLE);
	BABELTRADER_JSON_GET_INT(pipe_size, doc, "pipe_size", BABELTRADER_DEFAULT_PIPE_SIZE);

	return true;
}

NS_BABELTRADER_END
