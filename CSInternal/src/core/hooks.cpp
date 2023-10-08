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
	MH_EnableHook(MH_ALL_HOOKS);
}

void hooks::Destroy()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

bool __stdcall hooks::CreateMove(float frameTime, CUserCmd* cmd)
{
	const bool result = oCreateMove(interfaces::clientMode, frameTime, cmd);

	if (!cmd->commandNumber) { return result; }

	if (result) { interfaces::engine->SetViewAngles(cmd->viewAngles); }

	globals::localPlayer = interfaces::entityList->FromIndex<CCSPlayer*>(interfaces::engine->GetLocalPlayerIndex());

	if (!GetAsyncKeyState(VK_CONTROL) & 1) { return false; }

	if (!globals::localPlayer || !globals::localPlayer->IsAlive()) { return false; }

	Vector3 eyePos = globals::localPlayer->GetEyePosition();
	Vector3 aimPunch = globals::localPlayer->GetAimPunch();

	Vector3 dst = eyePos + Vector3{ cmd->viewAngles + aimPunch }.ToVector3() * 5000.f;

	CTrace trace;
	interfaces::trace->TraceRay({ eyePos, dst }, 0x46004009, globals::localPlayer, trace);

	if (!trace.entity
		|| !trace.entity->IsPlayer()
		|| !trace.entity->IsAlive()
		|| trace.entity->GetTeam() == globals::localPlayer->GetTeam()) {
		return false;
	}

	cmd->buttons |= IN_ATTACK;
	return false;
}
