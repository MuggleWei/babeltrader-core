/******************************************************************************
 *  @file         log.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-07-02
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader log
 *****************************************************************************/

#ifndef BABELTRADER_LOG_H_
#define BABELTRADER_LOG_H_

#include "babeltrader/base/defines/macro.h"

NS_BABELTRADER_BEGIN

#ifdef BABELTRADER_USE_LOG_MACRO

// user mugglec log by default
#define LOG_TRACE(format, ...) MUGGLE_LOG_DEFAULT(MUGGLE_LOG_LEVEL_TRACE, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) MUGGLE_LOG_DEFAULT(MUGGLE_LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) MUGGLE_LOG_DEFAULT(MUGGLE_LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) MUGGLE_LOG_DEFAULT(MUGGLE_LOG_LEVEL_WARNING, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) MUGGLE_LOG_DEFAULT(MUGGLE_LOG_LEVEL_ERROR, format, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) MUGGLE_LOG_DEFAULT(MUGGLE_LOG_LEVEL_FATAL, format, ##__VA_ARGS__)

#define LOG_LEVEL_TRACE MUGGLE_LOG_LEVEL_TRACE
#define LOG_LEVEL_DEBUG MUGGLE_LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO MUGGLE_LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING MUGGLE_LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR MUGGLE_LOG_LEVEL_ERROR
#define LOG_LEVEL_FATAL MUGGLE_LOG_LEVEL_FATAL

#endif

/**
 * @brief simple initialize log with console and file_rotate category
 *
 * @param level_console       console output level
 * @param level_file_rotating file rotating output level
 *
 * @return 
 *     0 - success
 *     otherwise - failed
 */
class Log
{
public:
	/**
	 * @brief simple initialize log with console and file time rotate handler
	 *
	 * @param level_console  console output level
	 * @param filepath       file path, if NULL, don't use file time roate handler
	 * @param level_file     file time rotating output level
	 *
	 * @return boolean value
	 */
	BABELTRADER_EXPORT
	static bool Init(int level_console, const char *filepath, int level_file);
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_LOG_H_ */
