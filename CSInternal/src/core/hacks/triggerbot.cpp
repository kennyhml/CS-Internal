#include "../hacks.h"
#include "../interfaces.h"
#include "../../csgo/interfaces/ienginetraceclient.h"

static bool HitEnemy(const CTrace& trace)
{
	return (trace.entity
		&& trace.entity->IsPlayer()
		&& trace.entity->IsAlive()
		&& trace.entity->GetTeam() != globals::localPlayer->GetTeam());
}

void hacks::TriggerBot(CUserCmd* cmd)
{
	if (!globals::localPlayer
		|| !globals::localPlayer->IsAlive()
		|| !(GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
		return;
	}

	Vector3 eyePos = globals::localPlayer->GetEyePosition();
	Vector3 aimPunch = globals::localPlayer->GetAimPunch();
	Vector3 dst = eyePos + Vector3{ cmd->viewAngles + aimPunch }.ToVector3() * 5000.f;

	CTrace trace;
	interfaces::trace->TraceRay({ eyePos, dst }, 0x46004009, globals::localPlayer, trace);

	if (HitEnemy(trace)) { cmd->buttons |= IN_ATTACK; }

}