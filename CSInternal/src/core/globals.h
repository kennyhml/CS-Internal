#pragma once
#include "../csgo/entity/ccsplayer.h"

namespace globals
{
	inline CCSPlayer* localPlayer = nullptr;
	inline uintptr_t clientAddr = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));

}