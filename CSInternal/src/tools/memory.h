#pragma once
#include <cstdint>
#include <Windows.h>

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}


namespace memory
{
	struct Signature
	{
		Signature(const char* module, const char* signature, int offset = 0)
			: module(module), signature(signature), offset(offset) {};

		const char* module;
		const char* signature;
		const int offset;

		BYTE* foundAt = nullptr;
	};

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

	BYTE* FindPattern(const char* moduleName, const char* pattern, int offset = 0);
	BYTE* FindPattern(Signature signature);

	inline namespace signatures
	{
		inline Signature forceUpdate("engine.dll", "A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85");
		inline Signature glowObjectManager("client.dll", "0F 11 05 ? ? ? ? 83 C8 01", 3);
		inline Signature weaponSystem("client.dll", "8B 35 ? ? ? ? FF 10 0F B7 C0", 2);
		inline Signature clientMode("client.dll", "55 8B EC 8B 0D ?? ?? ?? ?? 8B 01 5D FF 60", 5);
		inline Signature globals("client.dll", "74 1A A1 ?? ?? ?? ?? F3 0F 10 40 10", 3);

		inline Signature customMatInit("client.dll", "C6 86 ? ? ? ? ? FF 50 04", 2);
		inline Signature customMats("client.dll", "83 BE ? ? ? ? ? 7F 67", 2);
		inline Signature vDataProcessor("client.dll", "81 C7 ? ? ? ? 8B 4F 0C 8B 57 04 89 4C 24", 2);
	}
}
