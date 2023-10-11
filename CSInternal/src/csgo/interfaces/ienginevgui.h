#pragma once
#include "../../tools/memory.h"


enum EVGuiPanel
{
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

struct IEngineVGui
{
	uintptr_t GetPanel(int32_t type)
	{
		return memory::CallVmtFn<std::uintptr_t>(this, 1, type);
	}
};