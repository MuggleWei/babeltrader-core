/******************************************************************************
 *  @file         macro.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-09-28
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader api macro
 *****************************************************************************/

#ifndef BABELTRADER_API_MACRO_H_
#define BABELTRADER_API_MACRO_H_

#include "babeltrader/include/common_macro.h"

// export macro
#if WIN32 && defined(BABELTRADER_API_USE_DLL)
	#ifdef BABELTRADER_API_EXPORTS
		#define BABELTRADER_API_EXPORT __declspec(dllexport)
	#else
		#define BABELTRADER_API_EXPORT __declspec(dllimport)
	#endif
#else
	#define BABELTRADER_API_EXPORT
#endif

#endif /* ifndef BABELTRADER_API_MACRO_H_ */
