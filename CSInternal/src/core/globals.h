#pragma once
#include "../csgo/entity/ccsplayer.h"

namespace globals
{
	inline CCSPlayer* localPlayer = nullptr;
	inline uintptr_t clientAddr = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));
	inline uintptr_t engineAddr = reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll"));
	inline uintptr_t vguisurfaceAddr = reinterpret_cast<uintptr_t>(GetModuleHandle("vguimatsurface.dll"));
	inline uintptr_t vgui2Addr = reinterpret_cast<uintptr_t>(GetModuleHandle("vgui2.dll"));

}