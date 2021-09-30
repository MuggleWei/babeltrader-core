#include "enum.h"
#include <string>
#include <map>

/**
 * @brief macro define a string to enum class
 *
 * NOTE: need c++11 for static singleton
 */
#define BABELTRADER_ENUM_TO_STR_CLASS(str_array, enum_name, enum_max) \
class EnumClass##enum_name \
{ \
public: \
	EnumClass##enum_name() \
	{ \
		for (int i = 1; i < enum_max; i++) \
		{ \
			str_enum_map_[str_array[i]] = i; \
		} \
	} \
	virtual ~EnumClass##enum_name() {} \
\
	enum_name getEnum(const char *str_enum) \
	{ \
		auto it = str_enum_map_.find(str_enum); \
		if (it == str_enum_map_.end()) \
		{ \
			return (enum_name)0; \
		} \
		return (enum_name)it->second; \
	} \
private: \
	std::map<std::string, int> str_enum_map_; \
}; \
\
static EnumClass##enum_name & instance##enum_name() { \
	static EnumClass##enum_name instance; \
	return instance; \
}

/**
 * @brief macro define convert enum to string
 *
 * @param str_array string array
 * @param enum_name enum name
 * @param enum_max  max value in enum_name
 *
 * @return 
 *     - on success, return enum string name
 *     - on failed, return nullptr
 */
#define BABELTRADER_ENUM_TO_STR(str_array, enum_name, enum_max) \
const char* str##enum_name(int e) \
{ \
	if (e < 0 || e >= enum_max) \
	{ \
		return nullptr; \
	} \
	return str_array[e]; \
}

/**
 * @brief macro define string to enum
 *
 * @param enum_name enum name
 *
 * @return enum in enum_name
 */
#define BABELTRADER_STR_TO_ENUM(enum_name) \
enum_name get##enum_name(const char *s) \
{ \
	return instance##enum_name().getEnum(s); \
}

#define BABELTRADER_ENUM_CLASS(str_array, enum_name, enum_max) \
BABELTRADER_ENUM_TO_STR_CLASS(str_array, enum_name, enum_max) \
BABELTRADER_ENUM_TO_STR(str_array, enum_name, enum_max) \
BABELTRADER_STR_TO_ENUM(enum_name)

NS_BABELTRADER_BEGIN

static const char *s_apis[Api_Max] = {
	"",
	"ctp",
	"xtp",
	"okex"
};
BABELTRADER_ENUM_CLASS(s_apis, EnumApi, Api_Max);

static const char *s_exchanges[Exchange_Max] = {
	"",
	"SHFE",
	"CZCE",
	"DCE",
	"CFFEX",
	"INE",
	"SSE",
	"SZSE",
	"OKEX",
};
BABELTRADER_ENUM_CLASS(s_exchanges, EnumExchange, Exchange_Max);

static const char *s_product_types[ProductType_Max] = {
	"",
	"spot",
	"futures",
	"option"
};
BABELTRADER_ENUM_CLASS(s_product_types, EnumProductType, ProductType_Max);

static const char *s_quote_type[QuoteType_Max] = {
	"",
	"snapshot",
	"tick"
};
BABELTRADER_ENUM_CLASS(s_quote_type, EnumQuoteType, QuoteType_Max);

NS_BABELTRADER_END
