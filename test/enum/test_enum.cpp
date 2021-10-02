#include "gtest/gtest.h"
#include "babeltrader/base/babeltrader_base.h"

USING_NS_BABELTRADER;

TEST(Enum, EnumApi)
{
	const char *str = nullptr;
	for (int i = 0; i < API_Max; i++)
	{
		str = strEnumApi(i);
		ASSERT_TRUE(str != nullptr);

		ASSERT_EQ((int)getEnumApi(str), i);
	}

	ASSERT_STREQ(strEnumApi(API_CTP), "ctp");
	ASSERT_STREQ(strEnumApi(API_XTP), "xtp");
	ASSERT_STREQ(strEnumApi(API_OKEX), "okex");
	ASSERT_EQ(API_OKEX, API_Max - 1);
}

TEST(Enum, EnumExchange)
{
	const char *str = nullptr;
	for (int i = 0; i < EXCHANGE_Max; i++)
	{
		str = strEnumExchange(i);
		ASSERT_TRUE(str != nullptr);

		ASSERT_EQ((int)getEnumExchange(str), i);
	}

	ASSERT_STREQ(strEnumExchange(EXCHANGE_SHFE), "SHFE");
	ASSERT_STREQ(strEnumExchange(EXCHANGE_CZCE), "CZCE");
	ASSERT_STREQ(strEnumExchange(EXCHANGE_DCE), "DCE");
	ASSERT_STREQ(strEnumExchange(EXCHANGE_CFFEX), "CFFEX");
	ASSERT_STREQ(strEnumExchange(EXCHANGE_INE), "INE");
	ASSERT_STREQ(strEnumExchange(EXCHANGE_SSE), "SSE");
	ASSERT_STREQ(strEnumExchange(EXCHANGE_SZSE), "SZSE");
	ASSERT_STREQ(strEnumExchange(EXCHANGE_OKEX), "OKEX");
	ASSERT_EQ(EXCHANGE_OKEX, EXCHANGE_Max - 1);
}

TEST(Enum, EnumProductType)
{
	const char *str = nullptr;
	for (int i = 0; i < PRODUCT_TYPE_Max; i++)
	{
		str = strEnumProductType(i);
		ASSERT_TRUE(str != nullptr);

		ASSERT_EQ((int)getEnumProductType(str), i);
	}

	ASSERT_STREQ(strEnumProductType(PRODUCT_TYPE_SPOT), "spot");
	ASSERT_STREQ(strEnumProductType(PRODUCT_TYPE_FUTURES), "futures");
	ASSERT_STREQ(strEnumProductType(PRODUCT_TYPE_OPTION), "option");
	ASSERT_EQ(PRODUCT_TYPE_OPTION, PRODUCT_TYPE_Max - 1);
}

TEST(Enum, EnumQuoteType)
{
	const char *str = nullptr;
	for (int i = 0; i < QUOTE_TYPE_Max; i++)
	{
		str = strEnumQuoteType(i);
		ASSERT_TRUE(str != nullptr);

		ASSERT_EQ((int)getEnumQuoteType(str), i);
	}

	ASSERT_STREQ(strEnumQuoteType(QUOTE_TYPE_SNAPSHOT), "snapshot");
	ASSERT_STREQ(strEnumQuoteType(QUOTE_TYPE_TICK), "tick");
}
