#pragma once
#include "memory.h"
#include <stdexcept>
#include <vector>

static std::vector<int> PatternToBytes(const char* pattern)
{
	std::vector<int> result{};
	size_t patternLength = strlen(pattern);

	char* start = const_cast<char*>(pattern);
	char* end = start + patternLength;

	for (char* curr = start; curr < end; curr++)
	{
		if (*curr != '?') {
			result.push_back(std::strtoul(curr, &curr, 16));
		}
		else {
			while (*curr == '?') { curr++; }
			result.push_back(-1);
		}
	}
	return result;
}

BYTE* memory::FindPattern(const char* moduleName, const char* pattern)
{
	HMODULE handle = GetModuleHandle(moduleName);

	if (!handle) {
		throw std::runtime_error("Failed to get HMODULE of " + std::string(moduleName) + "!");
	}

	auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(handle);
	auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<BYTE*>(handle) + dosHeader->e_lfanew);

	auto bytes = PatternToBytes(pattern);

	size_t size = ntHeaders->OptionalHeader.SizeOfImage;
	BYTE* scanBytes = reinterpret_cast<BYTE*>(handle);

	size_t patternSize = bytes.size();
	int* byteData = bytes.data();

	for (int i = 0; i < size - patternSize; ++i)
	{
		bool found = true;
		for (int j = 0; j < patternSize; ++j)
		{
			if (scanBytes[i + j] != byteData[j] && byteData[j] != -1) {
				found = false;
				break;
			}
		}

		if (found)
			return &scanBytes[i];
	}
	throw std::runtime_error("Pattern not found: " + std::string(pattern));
}