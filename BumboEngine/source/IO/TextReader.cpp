#include "IO/TextReader.h"
#include <stdlib.h>

TextReader::TextReader(char *filePath)
	:currentFilePath(filePath)
{
	fopen_s(&pFile, currentFilePath, "rb+");

	if (pFile == nullptr)
	{
		fputs("File error", stderr);
	}

	isOpen = true;
}

TextReader::~TextReader()
{
}

void TextReader::Close()
{
	fclose(pFile);
	isOpen = false;
}

char* TextReader::ReadToEnd()
{
	if (isOpen)
	{
		long lSize;
		char *buffer;
		size_t result;

		fseek(pFile, 0, SEEK_END);
		lSize = ftell(pFile);
		rewind(pFile);

		buffer = (char*)malloc(sizeof(char)*(lSize + 1));
		if (buffer == NULL)
		{
			fputs("Memory error", stderr);
		}

		result = fread(buffer, 1, lSize, pFile);
		if (result != lSize)
		{
			fputs("Reading error", stderr);
		}

		buffer[lSize] = 0;

		return buffer;
	}
	return nullptr;
}