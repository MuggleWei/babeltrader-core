#include "quote_server_config.h"

#include <stdexcept>

#include "babeltrader/base/defines/enum.h"
#include "babeltrader/base/log/log.h"
#include "babeltrader/base/json/json_utils.h"
#include "babeltrader/base/defines/net_message.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/error/en.h"

NS_BABELTRADER_BEGIN

bool QuoteServerConfig::load(const char *file_path)
{
	FILE *fp = nullptr;
	char *buf = nullptr;

	fp = fopen(file_path, "rb");
	if (fp == nullptr)
	{
		LOG_ERROR("failed read quote config file: %s", file_path);
		return false;
	}

	bool ret = true;
	try {
		fseek(fp, 0, SEEK_END);
		long cnt = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		buf = (char*)malloc((size_t)cnt + 1);
		memset(buf, 0, cnt + 1);
		long read_cnt = (long)fread(buf, 1, cnt, fp);
		if (read_cnt != cnt)
		{
			LOG_ERROR("failed read config file: %s", file_path);
			throw std::logic_error("failed read config file");
		}

		rapidjson::Document doc;
		doc.Parse(buf);

		if (doc.HasParseError())
		{
			char err_msg[1024];
			rapidjson::ParseErrorCode err_code = doc.GetParseError();
			snprintf(err_msg, sizeof(err_msg),
				"failed parse json from config file: err_code=%d, offset=%d, err_msg=%s",
				(int)err_code, (int)doc.GetErrorOffset(), rapidjson::GetParseError_En(err_code));
			LOG_ERROR(err_msg);
			throw std::logic_error(err_msg);
		}

		if (!BABELTRADER_JSON_HAS_OBJ(doc, "quote_server"))
		{
			LOG_ERROR("can't find field 'quote_server' with object type");
			throw std::logic_error("can't find field 'quote_server' with object type");
		}
		rapidjson::Value &quote_doc = doc["quote_server"];

		BABELTRADER_JSON_GET_STR(tcp_listen_ip, quote_doc, "tcp_listen_ip", "");
		BABELTRADER_JSON_GET_INT(tcp_listen_port, quote_doc, "tcp_listen_port", 0);
		BABELTRADER_JSON_GET_STR(udp_send_ip, quote_doc, "udp_send_ip", "");
		BABELTRADER_JSON_GET_INT(udp_send_port, quote_doc, "udp_send_port", 0);
		BABELTRADER_JSON_GET_UINT(timer_interval, quote_doc, "timer_interval", BABELTRADER_DEFAULT_SERV_TIMER_INTERVAL);
		BABELTRADER_JSON_GET_UINT(idle_timeout, quote_doc, "idle_timeout", BABELTRADER_DEFAULT_SERV_IDLE);
		BABELTRADER_JSON_GET_UINT(event_pipe_size, quote_doc, "event_pipe_size", BABELTRADER_DEFAULT_PIPE_SIZE);
		BABELTRADER_JSON_GET_UINT(recv_unit_size, quote_doc, "recv_unit_size", BABELTRADER_DEFAULT_RECV_UNIT_SIZE);
		BABELTRADER_JSON_GET_UINT(max_msg_size, quote_doc, "max_msg_size", BABELTRADER_NET_MTU);
		BABELTRADER_JSON_GET_UINT(socket_bytes_buf_size, quote_doc, "socket_bytes_buf_size", BABELTRADER_DEFAULT_BYTES_BUF_SIZE);
		BABELTRADER_JSON_GET_UINT(hints_max_connect, quote_doc, "hints_max_connect", BABELTRADER_DEFAULT_HINTS_MAX_CONN);

		ret = onLoad(&doc);
	} catch (std::exception e) {
		LOG_ERROR(e.what());
		ret = false;
	}

	if (buf)
	{
		free(buf);
	}

	if (fp)
	{
		fclose(fp);
	}

	return ret;
}

bool QuoteServerConfig::onLoad(void *)
{
	return true;
}

void QuoteServerConfig::output()
{
	LOG_INFO("tcp_listen_ip=%s", tcp_listen_ip.c_str());
	LOG_INFO("tcp_listen_port=%d", tcp_listen_port);
	LOG_INFO("udp_send_ip=%s", udp_send_ip.c_str());
	LOG_INFO("udp_send_port=%d", udp_send_port);
	LOG_INFO("timer_interval=%lu", (unsigned long)timer_interval);
	LOG_INFO("idle_timeout=%lu", (unsigned long)idle_timeout);
	LOG_INFO("event_pipe_size=%lu", (unsigned long)event_pipe_size);
	LOG_INFO("recv_unit_size=%lu", (unsigned long)recv_unit_size);
	LOG_INFO("max_msg_size=%lu", (unsigned long)max_msg_size);
	LOG_INFO("socket_bytes_buf_size=%lu", (unsigned long)socket_bytes_buf_size);
	LOG_INFO("hints_max_connect=%lu", (unsigned long)hints_max_connect);
}

NS_BABELTRADER_END
