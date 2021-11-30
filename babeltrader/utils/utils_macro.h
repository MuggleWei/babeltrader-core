/******************************************************************************
 *  @file         utils_macro.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-11-01
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader utils macro
 *****************************************************************************/

#ifndef BABELTRADER_UTILS_MACRO_H_
#define BABELTRADER_UTILS_MACRO_H_

#include "babeltrader/include/common_macro.h"

// export macro
#if WIN32 && defined(BABELTRADER_UTILS_USE_DLL)
	#ifdef BABELTRADER_UTILS_EXPORTS
		#define BABELTRADER_UTILS_EXPORT __declspec(dllexport)
	#else
		#define BABELTRADER_UTILS_EXPORT __declspec(dllimport)
	#endif
#else
	#define BABELTRADER_UTILS_EXPORT
#endif  // BABELTRADER_UTILS_EXPORT

#endif /* ifndef BABELTRADER_UTILS_MACRO_H_ */
