#include "file_utils.h"

namespace LocalProject1
{
	std::string read_file(const char* file_path)
	{
		FILE* file = nullptr;
		if (fopen_s(&file, file_path, "rt") != 0 || file == nullptr) {
			return std::string();
		}
		fseek(file, 0, SEEK_END);
		unsigned long file_size = ftell(file);
		char* data = new char[file_size+1];
		memset(data, 0, file_size+1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, file_size, file);
		fclose(file);

		std::string result(data);
		delete[] data;

		return result;
	}
}