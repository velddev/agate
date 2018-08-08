#include <error_handling/exception.h>

Exception::Exception() {}
Exception::Exception(char* message) 
	: message(message)
{}
Exception::~Exception() {}

char* Exception::GetMessage()
{
    return message;
}