#include "../hacks.h"

void hacks::AntiFlash()
{
	if (!globals::localPlayer || !globals::localPlayer->IsAlive()) { return; }

	if (globals::localPlayer->FlashDuration() > 0.f) {
		globals::localPlayer->FlashDuration() = 0.f;
	}
}