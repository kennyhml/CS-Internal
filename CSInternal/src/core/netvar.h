#pragma once
#include "../csgo/datatable.h"
#include "../tools/hash.h"
#include <unordered_map>
#include <iostream>

inline std::unordered_map<std::uint32_t, std::uint32_t> netvars;

void SetupNetvars();
void DumpNetvars(const char* baseClass, RecvTable* table, std::uint32_t offset = 0);

#define NETVAR(name, var, ...) \
std::add_lvalue_reference_t<__VA_ARGS__> name() \
{ \
	static const auto offset = netvars[hash::HashConst(var)]; \
	return *reinterpret_cast<std::add_pointer_t<__VA_ARGS__>>(std::uintptr_t(this) + offset); \
}