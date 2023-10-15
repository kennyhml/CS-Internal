#pragma once
#include "../hooks.h"

void __stdcall hooks::PaintTraverse(uintptr_t panel, bool repaint, bool allowForce)
{
	hacks::esp::Run(panel);
	oPaintTraverse(interfaces::panel, panel, repaint, allowForce);
}