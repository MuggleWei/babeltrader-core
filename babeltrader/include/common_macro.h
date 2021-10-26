/******************************************************************************
 *  @file         common_macro.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-10-19
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader common macro
 *****************************************************************************/

#ifndef BABELTRADER_COMMON_MACRO_H_
#define BABELTRADER_COMMON_MACRO_H_

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

#endif /* ifndef BABELTRADER_MACRO_H_ */
