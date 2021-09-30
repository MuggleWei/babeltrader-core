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

#include "babeltrader/api/cpp/macro.h"
#include "babeltrader/api/cpp/struct.h"

NS_BABELTRADER_BEGIN

class BABELTRADER_API_EXPORT Spi
{
public:
	/**
	 * @brief babeltrader spi constructor
	 */
	Spi();

	/**
	 * @brief babeltrader spi destructor
	 */
	virtual ~Spi();

	/**
	 * @brief on api connected service
	 */
	virtual void OnConnected();

	/**
	 * @brief on api disconnected service
	 */
	virtual void OnDisconnected();

	/**
	 * @brief response login
	 *
	 * @param rsp       login response message
	 * @param err_info  error info
	 * @param req_id    request id
	 * @param is_last   is last response for this request
	 */
	virtual void OnRspLogin(RspLoginField *rsp, RspErrorInfo *err_info, int req_id, bool is_last);
};

class BABELTRADER_API_EXPORT Api
{
public:
	/**
	 * @brief babeltrader api constructor
	 */
	Api();

	/**
	 * @brief babeltrader api destructor
	 */
	virtual ~Api();

	/**
	 * @brief get api version
	 *
	 * @return api version
	 */
	virtual const char* GetVersion();

	/**
	 * @brief set log config
	 *
	 * @param filepath  log path, will create filepath if not exists
	 * @param level     filter log level, use BABELTRADER_LOG_LEVEL_*
	 *
	 * @note invoke this function before run
	 */
	virtual void SetLog(const char *filepath, int level) = 0;

	/**
	 * @brief register spi
	 *
	 * @param spi  callback function class
	 *
	 * @note invoke this function before run
	 */
	virtual void RegisterSpi(babeltrader::Spi *spi) = 0;

	/**
	 * @brief register service's address
	 *
	 * @param addr service's address
	 *
	 * @note  address's format: "protocol://ipaddress:port", for example: "tcp://127.0.0.1:10102"
	 */
	virtual void RegisterServiceAddr(const char *addr) = 0;

	/**
	 * @brief run api
	 */
	virtual void Run() = 0;

	/**
	 * @brief stop api
	 */
	virtual void Stop() = 0;

	/**
	 * @brief get current trading day
	 *
	 * @return  current trading day
	 *
	 * @note
	 * the trading day can only be obtained after successful login
	 */
	virtual const char* GetTradingDay() = 0;

	/**
	 * @brief request login
	 *
	 * @param req login request
	 *
	 * @return
	 *     0 - success send login request message
	 *     otherwise - error code in EnumErrId
	 */
	virtual int ReqLogin(ReqLoginField *req, int req_id) = 0;
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_API_TRADE_API_H_ */
