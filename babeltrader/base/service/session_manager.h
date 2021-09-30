/******************************************************************************
 *  @file         session_manager.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-09-06
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader session manager
 *****************************************************************************/

#ifndef BABELTRADER_SESSION_MANAGER_H_
#define BABELTRADER_SESSION_MANAGER_H_

#include "babeltrader/base/defines/macro.h"

NS_BABELTRADER_BEGIN

/**
 * @brief session manager
 */
class SessionManager
{
public:
	/**
	 * @brief session manager constructor
	 */
	BABELTRADER_EXPORT
	SessionManager();

	/**
	 * @brief session manager destructor
	 */
	BABELTRADER_EXPORT
	virtual ~SessionManager();

	/**
	 * @brief new session id
	 *
	 * @return  session id
	 */
	BABELTRADER_EXPORT
	uint64_t newSessionId();

private:
	uint64_t increase_id_;
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_SESSION_MANAGER_H_ */
