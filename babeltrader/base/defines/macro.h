/******************************************************************************
 *  @file         macro.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-01
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader macro
 *****************************************************************************/

#ifndef BABELTRADER_BASE_MACRO_H_
#define BABELTRADER_BASE_MACRO_H_

#include "muggle/cpp/muggle_cpp.h"
#include "babeltrader/api/cpp/api.h"

// lib and dll
#if MUGGLE_PLATFORM_WINDOWS && defined(BABELTRADER_USE_DLL)
	#ifdef BABELTRADER_EXPORTS
		#define BABELTRADER_EXPORT __declspec(dllexport)
	#else
		#define BABELTRADER_EXPORT __declspec(dllimport)
	#endif
#else
	#define BABELTRADER_EXPORT
#endif

#endif /* ifndef BABELTRADER_MACRO_H_ */
