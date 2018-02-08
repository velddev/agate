#pragma once
#include <string>

class File
{
public:
	static std::string GetWorkingDirectory();

	static char *LoadText(const char *fileName);
	static char *LoadText(char *fileName);
	static std::string LoadText(std::string fileName);

private:
	File();
	~File();
};