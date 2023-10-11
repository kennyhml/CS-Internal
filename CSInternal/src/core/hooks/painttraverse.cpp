#pragma once
#include "../hooks.h"

void __stdcall hooks::PaintTraverse(uintptr_t panel, bool repaint, bool allowForce)
{
	hacks::Esp(panel);
	oPaintTraverse(interfaces::panel, panel, repaint, allowForce);
}