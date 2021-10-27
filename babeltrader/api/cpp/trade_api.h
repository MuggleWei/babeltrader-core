/******************************************************************************
 *  @file         trade_api.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-09-30
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader trade api
 *****************************************************************************/

#ifndef BABELTRADER_API_TRADE_API_H_
#define BABELTRADER_API_TRADE_API_H_

#include "babeltrader/api/cpp/api_macro.h"

NS_BABELTRADER_BEGIN

class BABELTRADER_API_EXPORT TradeSpi
{
public:
	/**
	 * @brief babeltrader trade spi constructor
	 */
	TradeSpi();

	/**
	 * @brief babeltrader trade spi destructor
	 */
	virtual ~TradeSpi();

	/**
	 * @brief on api connected service
	 */
	virtual void OnConnected();

	/**
	 * @brief on api disconnected service
	 */
	virtual void OnDisconnected();
};

class BABELTRADER_API_EXPORT TradeApi
{
public:
	/**
	 * @brief babeltrader trade api constructor
	 */
	TradeApi();

	/**
	 * @brief babeltrader trade api destructor
	 */
	virtual ~TradeApi();

	/**
	 * @brief get api version
	 *
	 * @return api version
	 */
	virtual const char* GetVersion();

	/**
	 * @brief register spi
	 *
	 * @param spi  callback function class
	 *
	 * @note invoke this function before run
	 */
	virtual void RegisterSpi(babeltrader::TradeSpi *spi);

	/**
	 * @brief register service's address
	 *
	 * @param addr service's address
	 *
	 * @note  address's format: "protocol://ipaddress:port", for example: "tcp://127.0.0.1:10102"
	 */
	virtual void RegisterServiceAddr(const char *addr);

	/**
	 * @brief run api
	 */
	virtual void Run();

	/**
	 * @brief stop api
	 */
	virtual void Stop();

	/**
	 * @brief get current trading day
	 *
	 * @return  current trading day
	 *
	 * @note
	 * the trading day can only be obtained after successful login
	 */
	virtual const char* GetTradingDay();
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_API_TRADE_API_H_ */
