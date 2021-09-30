/******************************************************************************
 *  @file         test_utils_macro.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-26
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader test utils macro
 *****************************************************************************/

#ifndef BABELTRADER_TEST_UTILS_MACRO_H_
#define BABELTRADER_TEST_UTILS_MACRO_H_

#include "babeltrader/base/babeltrader_base.h"

// lib and dll
#if MUGGLE_PLATFORM_WINDOWS && defined(TESTUTILS_USE_DLL)
	#ifdef TESTUTILS_EXPORTS
		#define TESTUTILS_EXPORT __declspec(dllexport)
	#else
		#define TESTUTILS_EXPORT __declspec(dllimport)
	#endif
#else
	#define TESTUTILS_EXPORT
#endif


#endif /* ifndef BABELTRADER_TEST_UTILS_MACRO_H_ */
