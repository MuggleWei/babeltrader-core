/******************************************************************************
 *  @file         enum.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-09-28
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        
 *****************************************************************************/

#ifndef BABELTRADER_API_ENUM_H_
#define BABELTRADER_API_ENUM_H_

#include "babeltrader/api/cpp/macro.h"

NS_BABELTRADER_BEGIN

/**
 * @brief Market API enum
 */
enum EnumApi
{
	Api_Unknown = 0,
	Api_CTP,    //!< CTP
	Api_XTP,    //!< XTP
	Api_OKEX,   //!< OKEX
	Api_Max,
};
BABELTRADER_API_EXPORT
const char* strEnumApi(int market);
BABELTRADER_API_EXPORT
EnumApi getEnumApi(const char *market);

/**
 * @brief Exchange enum
 */
enum EnumExchange
{
	Exchange_Unknown = 0,
	Exchange_SHFE,   //!< Shanghai Futures Exchange
	Exchange_CZCE,   //!< Zhengzhou Commodities Exchange
	Exchange_DCE,    //!< Dalian Commodity Exchange
	Exchange_CFFEX,  //!< China Financial Futures Exchange
	Exchange_INE,    //!< Shanghai International Energy Exchange
	Exchange_SSE,    //!< Shanghai Stock Exchange
	Exchange_SZSE,   //!< Shenzhen Stock Exchange
	Exchange_OKEX,   //!< OKEX
	Exchange_Max,
};
BABELTRADER_API_EXPORT
const char* strEnumExchange(int exchange);
BABELTRADER_API_EXPORT
EnumExchange getEnumExchange(const char *exchange);

/**
 * @brief Product type enum
 */
enum EnumProductType
{
	ProductType_Unknown = 0,
	ProductType_Spot,    //!< spot
	ProductType_Futures, //!< futures
	ProductType_Option,  //!< option
	ProductType_Max,
};
BABELTRADER_API_EXPORT
const char* strEnumProductType(int product_type);
BABELTRADER_API_EXPORT
EnumProductType getEnumProductType(const char *product_type);

/**
 * @brief quote type enum
 */
enum EnumQuoteType
{
	QuoteType_Unknown = 0,
	QuoteType_Snapshot, //!< snapshot, include last price and n bid&ask
	QuoteType_Tick,     //!< tick data
	QuoteType_Max,
};
BABELTRADER_API_EXPORT
const char* strEnumQuoteType(int quote_type);
BABELTRADER_API_EXPORT
EnumQuoteType getEnumQuoteType(const char *quote_type);

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_API_ENUM_H_ */
