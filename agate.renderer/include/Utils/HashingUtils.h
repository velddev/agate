#pragma once
#include <cstdint>

class HashingUtils
{
public:
	static std::uint64_t Djb2(char *str);

private:
	HashingUtils() {}
	~HashingUtils() {}

};

