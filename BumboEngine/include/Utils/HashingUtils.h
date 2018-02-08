#pragma once
#include <cstdint>

class HashingUtils
{
public:
	static std::uint64_t Djb2(unsigned char *str);

private:
	HashingUtils() {}
	~HashingUtils() {}

};

