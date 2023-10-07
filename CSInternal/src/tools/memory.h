#pragma once
#include <cstdint>
#include <Windows.h>

namespace memory
{
	template <typename Return, typename ... Args>
	Return Call(void* _this, const uintptr_t index, Args ... args) noexcept
	{
		using Function = Return(__thiscall*)(void*, decltype(args)...);
		return (*static_cast<Function**>(_this))[index](_this, args...);
	}

	inline void* Get(void* _this, const uintptr_t index) noexcept
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