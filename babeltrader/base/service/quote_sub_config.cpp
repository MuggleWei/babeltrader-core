#include "quote_sub_config.h"
#include <set>
#include <string>
#include "babeltrader/base/log/log.h"
#include "babeltrader/base/json/json_utils.h"
#include "babeltrader/base/defines/enum.h"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

NS_BABELTRADER_BEGIN

bool QuoteSubConfig::load(const char *file_path)
{
	instruments.clear();
	std::set<std::string> instrument_set;

	FILE *fp = nullptr;
	char *buf = nullptr;

	fp = fopen(file_path, "rb");
	if (fp == nullptr)
	{
		LOG_ERROR("failed read subscription config file: %s", file_path);
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
			LOG_ERROR("failed read subscription config file: %s", file_path);
			throw(std::runtime_error("failed read subscription config file"));
		}

		rapidjson::Document doc;
		doc.Parse(buf);

		if (doc.HasParseError())
		{
			LOG_ERROR("failed parse json from subscription config file");
			throw(std::logic_error("failed parse json from subscription config file"));
		}

		BABELTRADER_JSON_GET_BOOL(sub_all, doc, "sub_all", false);
		if (sub_all)
		{
			LOG_ERROR("ctp subscription not support sub all");
			throw(std::logic_error("ctp subscription not support sub all"));
		}

		if (!doc.HasMember("instruments") || !doc["instruments"].IsArray())
		{
			LOG_ERROR("failed find instruments node in subscription config file");
			throw(std::logic_error("failed find instruments node in subscription config file"));
		}

		auto sub_array = doc["instruments"].GetArray();
		for (rapidjson::SizeType i = 0; i < sub_array.Size(); i++)
		{
			std::string str_quote_type;
			std::string str_api;
			std::string str_exchange;
			std::string str_product_type;
			std::string product_id;
			std::string instrument_id;
			BABELTRADER_JSON_GET_STR(str_quote_type, sub_array[i], "quote_type", "");
			BABELTRADER_JSON_GET_STR(str_api, sub_array[i], "api", "");
			BABELTRADER_JSON_GET_STR(str_exchange, sub_array[i], "exchange", "");
			BABELTRADER_JSON_GET_STR(str_product_type, sub_array[i], "product_type", "");
			BABELTRADER_JSON_GET_STR(product_id, sub_array[i], "product_id", "");
			BABELTRADER_JSON_GET_STR_THROW(instrument_id, sub_array[i], "instrument_id");

			EnumQuoteType quote_type = getEnumQuoteType(str_quote_type.c_str());
			EnumApi api = getEnumApi(str_api.c_str());
			EnumExchange exchange_id = getEnumExchange(str_exchange.c_str());
			EnumProductType product_type = getEnumProductType(str_product_type.c_str());
			if (product_id.size() >= sizeof(Instrument::product_id))
			{
				LOG_ERROR("length of product_id beyond the limit: %s, ignore",
						instrument_id.c_str());
				continue;
			}
			if (instrument_id.size() >= sizeof(Instrument::instrument_id))
			{
				LOG_ERROR("length of instrument_id beyond the limit: %s, ignore",
						instrument_id.c_str());
				continue;
			}

			char key[256];
			snprintf(key, sizeof(key), "%d_%d_%d_%d_%s$%s",
					(int)quote_type, (int)api, (int)exchange_id,
					(int)product_type, product_id.c_str(), instrument_id.c_str());
			if (instrument_set.find(key) != instrument_set.end())
			{
				LOG_WARNING(
					"ignore repeated sub item:"
					"quote_type=%s, api=%s, exchange=%s"
					"product_type=%s, product_id=%s, instrument_id=%s",
					str_quote_type.c_str(), str_api.c_str(), str_exchange.c_str(),
					str_product_type.c_str(), product_id.c_str(), instrument_id.c_str());
				continue;
			}
			instrument_set.insert(key);

			Instrument instrument;
			memset(&instrument, 0, sizeof(instrument));
			instrument.api = api;
			instrument.exchange = exchange_id;
			instrument.product_type = product_type;
			if (product_id.size() > 0)
			{
				strncpy(instrument.product_id, product_id.c_str(),
					sizeof(instrument.product_id)-1);
			}
			strncpy(instrument.instrument_id, instrument_id.c_str(),
					sizeof(instrument.instrument_id)-1);

			auto it = instruments.find(quote_type);
			if (it == instruments.end())
			{
				instruments[quote_type] = std::list<Instrument>();
				it = instruments.find(quote_type);
			}
			it->second.push_back(instrument);
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

bool QuoteSubConfig::onLoad(void*)
{
	return true;
}

void QuoteSubConfig::output()
{
	LOG_INFO("sub_all=%s", sub_all ? "true" : "false");
	for (auto it = instruments.begin(); it != instruments.end(); it++)
	{
		int quote_type = it->first;
		std::list<Instrument> &instrument_list = it->second;
		for (Instrument &instrument : instrument_list)
		{
			LOG_INFO(
				"sub instrument: "
				"quote_type=%s, api=%s, exchange=%s, "
				"product_type=%s, product_id=%s, instrument_id=%s",
				strEnumQuoteType(quote_type),
				strEnumApi((int)instrument.api),
				strEnumExchange((int)instrument.exchange),
				strEnumProductType((int)instrument.product_type),
				instrument.product_id,
				instrument.instrument_id
			);
		}
	}
}

NS_BABELTRADER_END
