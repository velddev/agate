#pragma once

class String
{
public:
	String();
	~String();

	String operator+=(String other);

private: 
	char* letters;
};

