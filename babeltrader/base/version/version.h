/******************************************************************************
 *  @file         version.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-07
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader version
 *****************************************************************************/

#ifndef BABELTRADER_VERSION_H_
#define BABELTRADER_VERSION_H_

#include "babeltrader/base/defines/macro.h"

NS_BABELTRADER_BEGIN

/**
 * @brief get babeltrader version
 *
 * @return babeltrader version
 */
BABELTRADER_EXPORT
const char* version();

/**
 * @brief get babeltrader compile time
 *
 * @return babeltrader compile time
 */
BABELTRADER_EXPORT
const char* compile_time();

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_VERSION_H_ */
