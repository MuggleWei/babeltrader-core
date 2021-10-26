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

std::string TestUtils::DumpBytesToHex(void *data, uint32_t data_len)
{
	uint32_t hex_len = data_len * 3 + 1;
	char *buf = (char*)malloc((size_t)hex_len);
	memset(buf, 0, hex_len);

	char *bytes = (char*)data;
	char *p = bytes;
	for (uint32_t i = 0; i < data_len; i++)
	{
		p = buf + i*3;
		if ((i+1) % 16 == 0)
		{
			snprintf(p, 4, "%02x\n", (unsigned char)bytes[i]);
		}
		else
		{
			snprintf(p, 4, "%02x ", (unsigned char)bytes[i]);
		}
	}

	std::string s = buf;
	free(buf);

	return s;
}

NS_BABELTRADER_END
