#include "json_config.h"

#include "babeltrader/utils/json_utils.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/error/en.h"

NS_BABELTRADER_BEGIN

JsonConfig::JsonConfig()
{}

JsonConfig::~JsonConfig()
{}

bool JsonConfig::load(const char *file_path)
{
	FILE *fp = nullptr;
	char *buf = nullptr;

	fp = fopen(file_path, "rb");
	if (fp == nullptr)
	{
		LOG_ERROR("failed read config file: %s", file_path);
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
				"failed parse json from file: err_code=%d, offset=%d, err_msg=%s",
				(int)err_code, (int)doc.GetErrorOffset(), rapidjson::GetParseError_En(err_code));
			LOG_ERROR(err_msg);
			throw std::logic_error(err_msg);
		}

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

bool JsonConfig::onLoad(void *)
{
	return true;
}

NS_BABELTRADER_END
