#pragma once
#include <cstdint>

#define BASE 0x811C9DC5
#define PRIME 0x1000193

namespace hash
{
	uint32_t HashConst(const char* data, const uint32_t seed = BASE);
	uint32_t Hash(const char* data);
}