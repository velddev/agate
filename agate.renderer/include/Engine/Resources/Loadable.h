#pragma once
#include <string>
#include <vector>

class Loadable
{
public:
	virtual void Load(char *filePath) = 0;
	virtual void Load(std::vector<std::string> filePaths) = 0;
};