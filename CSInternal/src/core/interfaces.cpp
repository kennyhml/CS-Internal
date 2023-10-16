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
	panel = GetInterface<IPanel>("VGUI_Panel009", "vgui2.dll");
	engineVGui = GetInterface<IEngineVGui>("VEngineVGui001", "engine.dll");
	debugOverlay = GetInterface<IDebugOverlay>("VDebugOverlay004", "engine.dll");
	surface = GetInterface<ISurface>("VGUI_Surface031", "vguimatsurface.dll");
	modelInfo = GetInterface<IModelInfo>("VModelInfoClient004", "engine.dll");

	glow = *reinterpret_cast<IGlowObjectManager**>(memory::FindPattern(memory::signatures::glowObjectManager));
	weapons = *reinterpret_cast<IWeaponSystem**>(memory::FindPattern(memory::signatures::weaponSystem));
	clientMode = **reinterpret_cast<IClientMode***>(memory::FindPattern(memory::signatures::clientMode));
	globals = **reinterpret_cast<IGlobalVarsBase***>(memory::FindPattern(memory::signatures::globals));

	// two different ways to get the p_mMemAlloc singleton, GetProcAddress is more reliable tho.
	// memAlloc = ***reinterpret_cast<IMemAlloc****>(memory::FindPattern(memory::signatures::memAlloc));
	memAlloc = *reinterpret_cast<IMemAlloc**>(GetProcAddress(GetModuleHandleA("tier0.dll"), "g_pMemAlloc"));
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