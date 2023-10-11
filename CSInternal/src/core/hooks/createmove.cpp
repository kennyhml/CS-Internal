#include "../hooks.h"
#include "../../csgo/cusercmd.h"

bool __stdcall hooks::CreateMove(float frameTime, CUserCmd* cmd)
{
	const bool result = oCreateMove(interfaces::clientMode, frameTime, cmd);
	if (!cmd->commandNumber) { return result; }

	hacks::BunnyHop(cmd);
	hacks::TriggerBot(cmd);

	if (result) { interfaces::engine->SetViewAngles(cmd->viewAngles); }
	hacks::Aimbot(cmd);

	return false;
}