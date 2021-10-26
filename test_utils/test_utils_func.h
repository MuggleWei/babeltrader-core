/******************************************************************************
 *  @file         test_utils_func.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-26
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader test utils function
 *****************************************************************************/

#ifndef BABELTRADER_TEST_UTILS_FUNC_H_
#define BABELTRADER_TEST_UTILS_FUNC_H_

#include "test_utils/test_utils_macro.h"

NS_BABELTRADER_BEGIN

class TestUtils
{
public:
	/**
	 * @brief get test output path, if output dir not exists, will create automaticlly
	 *
	 * @param dir_name output directroy, relative path to current process directory
	 * @param filename file name
	 *
	 * @return output file path
	 */
	TESTUTILS_EXPORT
	static std::string GetOutputPath(const char *dir_name, const char *filename);

	/**
	 * @brief write string into file
	 *
	 * @param str      string
	 * @param filepath target file path
	 *
	 * @return boolean
	 */
	TESTUTILS_EXPORT
	static bool writeFile(std::string &str, const char *filepath);

	/**
	 * @brief convert bytes array to hex string
	 *
	 * @param data      bytes array
	 * @param data_len  length of bytes array
	 *
	 * @return hex string
	 */
	TESTUTILS_EXPORT
	static std::string DumpBytesToHex(void *data, uint32_t data_len);
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_TEST_UTILS_FUNC_H_ */
