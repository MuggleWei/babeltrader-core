#include "gtest/gtest.h"
#include "babeltrader/base/babeltrader_base.h"

USING_NS_BABELTRADER;

TEST(Enum, EnumApi)
{
	const char *str = nullptr;
	for (int i = 0; i < Api_Max; i++)
	{
		str = strEnumApi(i);
		ASSERT_TRUE(str != nullptr);

		ASSERT_EQ((int)getEnumApi(str), i);
	}

	ASSERT_STREQ(strEnumApi(Api_CTP), "ctp");
	ASSERT_STREQ(strEnumApi(Api_XTP), "xtp");
	ASSERT_STREQ(strEnumApi(Api_OKEX), "okex");
	ASSERT_EQ(Api_OKEX, Api_Max - 1);
}

TEST(Enum, EnumExchange)
{
	const char *str = nullptr;
	for (int i = 0; i < Exchange_Max; i++)
	{
		str = strEnumExchange(i);
		ASSERT_TRUE(str != nullptr);

		ASSERT_EQ((int)getEnumExchange(str), i);
	}

	ASSERT_STREQ(strEnumExchange(Exchange_SHFE), "SHFE");
	ASSERT_STREQ(strEnumExchange(Exchange_CZCE), "CZCE");
	ASSERT_STREQ(strEnumExchange(Exchange_DCE), "DCE");
	ASSERT_STREQ(strEnumExchange(Exchange_CFFEX), "CFFEX");
	ASSERT_STREQ(strEnumExchange(Exchange_INE), "INE");
	ASSERT_STREQ(strEnumExchange(Exchange_SSE), "SSE");
	ASSERT_STREQ(strEnumExchange(Exchange_SZSE), "SZSE");
	ASSERT_STREQ(strEnumExchange(Exchange_OKEX), "OKEX");
	ASSERT_EQ(Exchange_OKEX, Exchange_Max - 1);
}

TEST(Enum, EnumProductType)
{
	const char *str = nullptr;
	for (int i = 0; i < ProductType_Max; i++)
	{
		str = strEnumProductType(i);
		ASSERT_TRUE(str != nullptr);

		ASSERT_EQ((int)getEnumProductType(str), i);
	}

	ASSERT_STREQ(strEnumProductType(ProductType_Spot), "spot");
	ASSERT_STREQ(strEnumProductType(ProductType_Futures), "futures");
	ASSERT_STREQ(strEnumProductType(ProductType_Option), "option");
	ASSERT_EQ(ProductType_Option, ProductType_Max - 1);
}

TEST(Enum, EnumQuoteType)
{
	const char *str = nullptr;
	for (int i = 0; i < QuoteType_Max; i++)
	{
		str = strEnumQuoteType(i);
		ASSERT_TRUE(str != nullptr);

		ASSERT_EQ((int)getEnumQuoteType(str), i);
	}

	ASSERT_STREQ(strEnumQuoteType(QuoteType_Snapshot), "snapshot");
	ASSERT_STREQ(strEnumQuoteType(QuoteType_Tick), "tick");
}
