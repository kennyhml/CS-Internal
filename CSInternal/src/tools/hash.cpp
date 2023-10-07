#include "hash.h"
#include <cstring>

uint32_t hash::HashConst(const char* data, const uint32_t seed)
{
	return (data[0] == '\0') ? seed : HashConst(&data[1], (seed ^ uint32_t(data[0])) * PRIME);
}

uint32_t hash::Hash(const char* data)
{
	uint32_t hashed = BASE;

	for (size_t i = 0U; i < strlen(data); ++i)
	{
		hashed ^= data[i];
		hashed *= PRIME;
	}

	return hashed;
}