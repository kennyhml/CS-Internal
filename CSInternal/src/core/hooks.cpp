#include "hooks.h"
#include "interfaces.h"
#include "../../ext/minhook/MinHook.h"
#include "../tools/memory.h"
#include "../csgo/cusercmd.h"

void hooks::Init()
{
	MH_Initialize();

	MH_CreateHook(
		memory::GetVmtFn(interfaces::clientMode, 24),
		&CreateMove,
		reinterpret_cast<void**>(&oCreateMove)
	);

	MH_CreateHook(
		memory::GetVmtFn(interfaces::render, 29),
		&DrawModel,
		reinterpret_cast<void**>(&oDrawModel)
	);

	MH_CreateHook(
		memory::GetVmtFn(interfaces::clientMode, 44),
		&DoPostScreenSpaceEffects,
		reinterpret_cast<void**>(&oDoPostScreenSpaceEffects)
	);

	MH_CreateHook(
		memory::GetVmtFn(interfaces::panel, 41),
		&PaintTraverse,
		reinterpret_cast<void**>(&oPaintTraverse)
	);

	MH_EnableHook(MH_ALL_HOOKS);
}

void hooks::Destroy()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

