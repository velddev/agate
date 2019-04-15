#include <memory>
#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#endif

#include "IO/filesystem/File.h"
#include "IO/TextReader.h"

File::File()
{
}

File::~File()
{
}

std::string File::GetWorkingDirectory()
{
	char temp[1024];
	getcwd(temp, 1024);
	return std::string(temp);
}

char *File::LoadText(const char *fileName)
{
	return LoadText((char*)fileName);
}
char *File::LoadText(char *fileName)
{
	std::unique_ptr<TextReader> tr = std::make_unique<TextReader>(fileName);
	char *result = tr->ReadToEnd();
	tr->Close();
	return result;
}
std::string File::LoadText(std::string fileName)
{
	return std::string(LoadText(fileName.c_str()));
}