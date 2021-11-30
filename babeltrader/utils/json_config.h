/******************************************************************************
 *  @file         json_config.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-11-01
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader utils json config
 *****************************************************************************/

#ifndef BABELTRADER_UTILS_JSON_CONFIG_H_
#define BABELTRADER_UTILS_JSON_CONFIG_H_

#include "babeltrader/utils/utils_macro.h"

NS_BABELTRADER_BEGIN

class JsonConfig
{
public:
	BABELTRADER_UTILS_EXPORT
	JsonConfig();

	BABELTRADER_UTILS_EXPORT
	virtual ~JsonConfig();

	BABELTRADER_UTILS_EXPORT
	bool load(const char *file_path);

	BABELTRADER_UTILS_EXPORT
	virtual bool onLoad(void *json_doc);
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_UTILS_JSON_CONFIG_H_ */
