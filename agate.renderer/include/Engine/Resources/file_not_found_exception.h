#pragma once
#include <exception>
#include <stdio.h>

namespace agate {
	class FileNotLoadedException
		: public std::exception
	{
	public:
		FileNotLoadedException(const char* path)
			: exception(formatMsg(path)) {}

	private:
		char* formatMsg(const char* path) {
			const char* format = "Could not load file from path '%s'.";
			char* errorMsg = new char[256];
			sprintf_s(errorMsg, 256, format, path);
			return errorMsg;
		}
	};
}