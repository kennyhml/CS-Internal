#pragma once
#include "../util/fnv.h"
#include "../csgo/datatable.h"
#include <unordered_map>
#include <iostream>

void SetupNetvars();
void Dump(const char* baseClass, RecvTable* table, std::uint32_t offset = 0);

inline std::unordered_map<std::uint32_t, std::uint32_t> netvars;

#define NETVAR(func_name, netvar, type) type& func_name() \
{ \
	static int offset = netvars[fnv::HashConst(netvar)]; \
	return *reinterpret_cast<type*>(std::uint32_t(this) + offset); \
}