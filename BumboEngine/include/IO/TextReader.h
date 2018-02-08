#pragma once
#include <stdio.h>

class TextReader
{
public:
	TextReader(char *filePath);
	~TextReader();

	void Close();

	char *ReadToEnd();

private:
	char *currentFilePath;
	bool isOpen = false;

	FILE *pFile = nullptr;
};