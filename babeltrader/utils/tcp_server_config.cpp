#include "tcp_server_config.h"

#include "babeltrader/base/defines/enum.h"
#include "babeltrader/utils/json_utils.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/error/en.h"

NS_BABELTRADER_BEGIN

TcpServerConfig::TcpServerConfig()
	: JsonConfig()
	, host("")
	, port(0)
	, msg_pool_size(BABELTRADER_DEFAULT_MSG_POOL_SIZE)
	, recv_unit_size(BABELTRADER_DEFAULT_RECV_UNIT_SIZE)
	, bytes_buf_size(BABELTRADER_DEFAULT_BYTES_BUF_SIZE)
	, hints_max_connect(BABELTRADER_DEFAULT_HINTS_MAX_CONN)
{}

TcpServerConfig::~TcpServerConfig()
{}

bool TcpServerConfig::onLoad(void *json_doc)
{
	rapidjson::Document *p_root_doc = (rapidjson::Document*)json_doc;
	rapidjson::Document &root_doc = *p_root_doc;

	if (!BABELTRADER_JSON_HAS_OBJ(root_doc, "tcp_server"))
	{
		LOG_ERROR("can't find field 'tcp_server' with object type");
		return false;
	}
	rapidjson::Value &doc = root_doc["tcp_server"];

	BABELTRADER_JSON_GET_STR(host, doc, "host", "");
	BABELTRADER_JSON_GET_INT(port, doc, "port", 0);
	BABELTRADER_JSON_GET_INT(msg_pool_size, doc, "msg_pool_size", 0);
	BABELTRADER_JSON_GET_INT(recv_unit_size, doc, "recv_unit_size", 0);
	BABELTRADER_JSON_GET_INT(bytes_buf_size, doc, "bytes_buf_size", 0);
	BABELTRADER_JSON_GET_INT(hints_max_connect, doc, "hints_max_connect", 0);

	return true;
}

NS_BABELTRADER_END
