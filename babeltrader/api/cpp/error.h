/******************************************************************************
 *  @file         error.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-09-28
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader error
 *****************************************************************************/

#ifndef BABELTRADER_API_ERROR_H_
#define BABELTRADER_API_ERROR_H_

#include "babeltrader/api/cpp/macro.h"

NS_BABELTRADER_BEGIN

enum EnumErrId
{
	ErrId_Ok = 0,
	ErrId_UpstreamErr,      //!< upstream error
	ErrId_Internal,         //!< internal error
	ErrId_MissField,        //!< field missing
	ErrId_UpstreamNotReady, //!< upstream server not ready yet
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_API_ERROR_H_ */
