#include "interfaces.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "../tools/memory.h"

void interfaces::Init()
{
	client = GetInterface<IClient>("VClient018", "client.dll");
	entityList = GetInterface<IClientEntityList>("VClientEntityList003", "client.dll");
	engine = GetInterface<IEngineClient>("VEngineClient014", "engine.dll");
	trace = GetInterface<IEngineTraceClient>("EngineTraceClient004", "engine.dll");
	render = GetInterface<IStudioRender>("VStudioRender026", "studiorender.dll");
	materialSystem = GetInterface<IMaterialSystem>("VMaterialSystem080", "materialsystem.dll");

	glow = *reinterpret_cast<IGlowObjectManager**>(memory::FindPattern("client.dll", "0F 11 05 ? ? ? ? 83 C8 01"));
	weapons = *reinterpret_cast<IWeaponSystem**>(memory::FindPattern("client.dll", "8B 35 ? ? ? ? FF 10 0F B7 C0") + 2);
	clientMode = **reinterpret_cast<IClientMode***>(memory::FindPattern("client.dll", "55 8B EC 8B 0D ?? ?? ?? ?? 8B 01 5D FF 60") + 5);
}

template <typename T>
T* interfaces::GetInterface(const char* name, const char* moduleName)
{
	HMODULE handle = GetModuleHandle(moduleName);

	if (!handle) { return nullptr; }

	uintptr_t addr = reinterpret_cast<uintptr_t>(GetProcAddress(handle, "CreateInterface"));
	if (!addr) { return nullptr; }

	using Fn = T * (*)(const char*, int*);
	const auto CreateInterface = reinterpret_cast<Fn>(addr);

	return CreateInterface(name, nullptr);
}