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
	API_UNKNOWN = 0,
	API_SIM,    //!< babeltrader simulation
	API_CTP,    //!< CTP
	API_XTP,    //!< XTP
	API_OKEX,   //!< OKEX
	API_Max,
};
BABELTRADER_API_EXPORT
const char* strEnumApi(int api_type);
BABELTRADER_API_EXPORT
EnumApi getEnumApi(const char *api_type);

/**
 * @brief Exchange enum
 */
enum EnumExchange
{
	EXCHANGE_UNKNOWN = 0,
	EXCHANGE_SHFE,   //!< Shanghai Futures Exchange
	EXCHANGE_CZCE,   //!< Zhengzhou Commodities Exchange
	EXCHANGE_DCE,    //!< Dalian Commodity Exchange
	EXCHANGE_CFFEX,  //!< China Financial Futures Exchange
	EXCHANGE_INE,    //!< Shanghai International Energy Exchange
	EXCHANGE_SSE,    //!< Shanghai Stock Exchange
	EXCHANGE_SZSE,   //!< Shenzhen Stock Exchange
	EXCHANGE_OKEX,   //!< OKEX
	EXCHANGE_Max,
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
	PRODUCT_TYPE_UNKNOWN = 0,
	PRODUCT_TYPE_SPOT,    //!< spot
	PRODUCT_TYPE_FUTURES, //!< futures
	PRODUCT_TYPE_OPTION,  //!< option
	PRODUCT_TYPE_Max,
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
	QUOTE_TYPE_UNKNOWN = 0,
	QUOTE_TYPE_SNAPSHOT, //!< snapshot, include last, bid and ask price/vol
	QUOTE_TYPE_TICK,     //!< tick data
	QUOTE_TYPE_Max,
};
BABELTRADER_API_EXPORT
const char* strEnumQuoteType(int quote_type);
BABELTRADER_API_EXPORT
EnumQuoteType getEnumQuoteType(const char *quote_type);

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_API_ENUM_H_ */
