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

// namespace
#ifdef __cplusplus
	#define NS_BABELTRADER_BEGIN namespace babeltrader {
	#define NS_BABELTRADER_END   }
	#define USING_NS_BABELTRADER using namespace babeltrader
#else
	#define NS_BABELTRADER_BEGIN
	#define NS_BABELTRADER_END  
	#define USING_NS_BABELTRADER
#endif 

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
