#include "log.h"

NS_BABELTRADER_BEGIN

bool Log::Init(int level_console, const char *filepath, int level_file)
{
	return muggle::Log::SimpleInit(level_console, filepath, level_file);
}

NS_BABELTRADER_END
