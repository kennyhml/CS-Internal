#pragma once
#include <cstdint>
#include <Windows.h>

namespace memory
{
	template <typename Return, typename ... Args>
	Return CallVmtFn(void* _this, const uintptr_t index, Args ... args) noexcept
	{
		using Function = Return(__thiscall*)(void*, decltype(args)...);
		return (*static_cast<Function**>(_this))[index](_this, args...);
	}

	inline void* GetVmtFn(void* _this, const uintptr_t index) noexcept
	{
		return (*static_cast<void***>(_this))[index];
	}

	BYTE* FindPattern(const char* moduleName, const char* pattern);

	inline namespace offsets
	{
		inline BYTE* setAbsOrigin = nullptr;
		inline BYTE* setAbsAngles = nullptr;
	}

}

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}
