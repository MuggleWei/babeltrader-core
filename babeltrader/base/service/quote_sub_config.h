/******************************************************************************
 *  @file         quote_sub_config.h
 *  @author       Muggle Wei
 *  @email        mugglewei@gmail.com
 *  @date         2021-08-28
 *  @copyright    Copyright 2021 Muggle Wei
 *  @license      MIT License
 *  @brief        babeltrader quote subscribe config
 *****************************************************************************/

#ifndef BABELTRADER_QUOTE_SUB_CONFIG_H_
#define BABELTRADER_QUOTE_SUB_CONFIG_H_

#include "babeltrader/base/defines/macro.h"
#include "babeltrader/base/defines/msg_struct.h"

#include <map>
#include <list>

NS_BABELTRADER_BEGIN

/**
 * @brief babeltrader common quote sub config
 */
class QuoteSubConfig
{
public:
	BABELTRADER_EXPORT
	bool load(const char *file_path);

	BABELTRADER_EXPORT
	virtual bool onLoad(void *json_doc);

	BABELTRADER_EXPORT
	virtual void output();

public:
	bool sub_all;
	std::map<uint32_t, std::list<Instrument>> instruments;
};

NS_BABELTRADER_END

#endif /* ifndef BABELTRADER_QUOTE_SUB_CONFIG_H_ */
