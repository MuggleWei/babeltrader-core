#include "version.h"

NS_BABELTRADER_BEGIN

#ifndef BABELTRADER_VER
	#define BABELTRADER_VER ?.?.?
#endif

#define BABELTRADER_COMPILRE_TIME __DATE__ " " __TIME__

const char* version()
{
	return MUGGLE_MACRO_STR(BABELTRADER_VER);
}

const char* compile_time()
{
	return BABELTRADER_COMPILRE_TIME;
}

NS_BABELTRADER_END
