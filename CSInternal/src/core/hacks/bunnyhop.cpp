#include "../hacks.h"

void hacks::BunnyHop(CUserCmd* cmd)
{
	if (!globals::localPlayer || !GetAsyncKeyState(VK_SPACE)
		|| globals::localPlayer->Flags() & FL_ONGROUND) {
		return;
	}
	// Send space to jump
	cmd->buttons &= ~IN_JUMP;
}


