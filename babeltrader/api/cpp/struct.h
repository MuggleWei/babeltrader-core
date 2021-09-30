/******************************************************************************
 *  @file         struct.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-09-30
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader api structures
 *****************************************************************************/

#ifndef BABELTRADER_API_STRUCT_H_
#define BABELTRADER_API_STRUCT_H_

#include "babeltrader/api/cpp/macro.h"
#include <stdint.h>

NS_BABELTRADER_BEGIN

#define BABELTRADER_LEN_ERR_MSG   128 //!< max length of error message
#define BABELTRADER_LEN_USER_ID   32  //!< max length of user id
#define BABELTRADER_LEN_PASSWORD  32  //!< max length of password
#define BABELTRADER_LEN_VERSION   32  //!< max length of version
#define BABELTRADER_LEN_SERV_NAME 32  //!< max length of service name

/**
 * @brief response error message
 */
struct RspErrorInfo
{
	uint64_t err_id;  //!< error id in EnumErrId
	char     err_msg; //!< error message
};

/**
 * @brief request login field
 */
struct ReqLoginField
{
	char user_id[BABELTRADER_LEN_USER_ID];   //!< user id
	char password[BABELTRADER_LEN_PASSWORD]; //!< password
};

/**
 * @brief response login field
 */
struct RspLoginField
{
	char     service_name[BABELTRADER_LEN_SERV_NAME]; //!< service name
	char     version[BABELTRADER_LEN_VERSION];        //!< service's version
	uint64_t service_id;                              //!< service id
	uint64_t session_id;                              //!< session id
	char     user_id[BABELTRADER_LEN_USER_ID];        //!< user id
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_API_STRUCT_H_ */
