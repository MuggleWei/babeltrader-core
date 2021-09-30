#include "test_utils.h"

NS_BABELTRADER_BEGIN

std::string TestUtils::GetOutputPath(const char *dir_name, const char *filename)
{
	char process_path[1024];
	muggle_os_process_path(process_path, sizeof(process_path));

	char process_dir[1024];
	muggle_path_dirname(process_path, process_dir, sizeof(process_dir));

	char output_dir[1024];
	muggle_path_join(process_dir, dir_name, output_dir, sizeof(output_dir));

	if (!muggle_path_exists(output_dir))
	{
		muggle_os_mkdir(output_dir);
	}

	char filepath[1024];
	muggle_path_join(output_dir, filename, filepath, sizeof(filepath));

	return filepath;
}

bool TestUtils::writeFile(std::string &str, const char *filepath)
{
	FILE *fp = fopen(filepath, "w");
	if (fp == nullptr)
	{
		return false;
	}

	if (fwrite(str.c_str(), 1, str.size(), fp) != str.size())
	{
		return false;
	}

	fclose(fp);

	return true;
}

NS_BABELTRADER_END
