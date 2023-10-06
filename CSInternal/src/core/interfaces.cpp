#include "interfaces.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void interfaces::Init()
{
	client = GetInterface<IClient>("VClient018", "client.dll");
	entityList = GetInterface<IClientEntityList>("VClientEntityList003", "client.dll");
	engine = GetInterface<IEngineClient>("VEngineClient014", "engine.dll");
	trace = GetInterface<IEngineTraceClient>("EngineTraceClient004", "engine.dll");

	clientMode = **reinterpret_cast<void***>((*reinterpret_cast<unsigned int**>(client))[10] + 5);
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