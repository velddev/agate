#pragma once

class Exception {
	char* message;

public:
	Exception();
	Exception(char* message);
	~Exception();

	char* GetMessage();
};