#pragma once

class TextReader
{
public:
	TextReader();
	~TextReader();

	void Close();

	void Open(char *filePath);

	void Flush();

	char *ReadToEnd();

private:
	char *currentFilePath;
	bool isOpen;
};