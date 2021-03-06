/******************************************************************************
 *  @file         enum.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-01
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader base enum
 *****************************************************************************/

#ifndef BABELTRADER_BASE_ENUM_H_
#define BABELTRADER_BASE_ENUM_H_

#include "babeltrader/base/defines/macro.h"

NS_BABELTRADER_BEGIN

#define BABELTRADER_DEFAULT_MSG_POOL_SIZE 1024 //!< default message pool size
#define BABELTRADER_DEFAULT_PIPE_SIZE 1024 //!< default pipe size
#define BABELTRADER_DEFAULT_RECV_UNIT_SIZE 4096 //!< default recv unit size
#define BABELTRADER_DEFAULT_BYTES_BUF_SIZE (4*1024*1024) //!< default bytes buffer size
#define BABELTRADER_DEFAULT_HINTS_MAX_CONN 512  //!< default hints max connect
#define BABELTRADER_DEFAULT_SERV_TIMER_INTERVAL (10*1000) //!< default timer interval
#define BABELTRADER_DEFAULT_SERV_IDLE 30 //!< default disconnect idle time

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_ENUM_H_ */
