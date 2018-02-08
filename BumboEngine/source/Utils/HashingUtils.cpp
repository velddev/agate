#include "Utils/HashingUtils.h"

std::uint64_t HashingUtils::Djb2(unsigned char * str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c;

	return hash;
}