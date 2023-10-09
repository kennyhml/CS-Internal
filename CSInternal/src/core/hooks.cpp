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

	MH_CreateHook(
		memory::GetVmtFn(interfaces::render, 29),
		&DrawModel,
		reinterpret_cast<void**>(&oDrawModel)
	);

	MH_CreateHook(
		memory::GetVmtFn(interfaces::clientMode, 44),
		&DoPostScreenSpaceEffects,
		reinterpret_cast<void**>(&oDoPostScreenSpaceEffects)
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

void __stdcall hooks::DrawModel(
	void* result,
	CDrawModelInfo& info,
	CMatrix3x4* bones,
	float* flexWeights,
	float* flexDelayedWeights,
	Vector3& modelOrigin,
	int flags)
{
	if (globals::localPlayer && info.renderable)
	{
		CBaseEntity* entity = info.renderable->GetClientUnknown()->GetBaseEntity();

		if (entity && entity->IsPlayer() 
			&& entity->GetTeam() != globals::localPlayer->GetTeam()
			&& !interfaces::render->IsForcedMaterialOverride())
		{
			static IMaterial* material = interfaces::materialSystem->FindMaterial("debug/debugambientcube");

			float hidden[3] = { 0.f, 1.f, 1.f };
			float visible[3] = { 1.f, 1.f, 0.f };

			interfaces::render->SetAlphaModulation(1.f);

			material->SetMaterialVarFlag(IMaterial::IGNOREZ, true);
			interfaces::render->SetColorModulation(hidden);
			interfaces::render->ForcedMaterialOverride(material);
			oDrawModel(interfaces::render, result, info, bones, flexWeights, flexDelayedWeights, modelOrigin, flags);

			material->SetMaterialVarFlag(IMaterial::IGNOREZ, false);
			interfaces::render->SetColorModulation(visible);
			interfaces::render->ForcedMaterialOverride(material);
			oDrawModel(interfaces::render, result, info, bones, flexWeights, flexDelayedWeights, modelOrigin, flags);

			return interfaces::render->ForcedMaterialOverride(nullptr);
		}
	}
	oDrawModel(interfaces::render, result, info, bones, flexWeights, flexDelayedWeights, modelOrigin, flags);
}

bool __stdcall hooks::DoPostScreenSpaceEffects(const CViewSetup* pSetup)
{

	if (globals::localPlayer && interfaces::engine->IsInGame())
	{
		for (int i = 0; i < interfaces::glow->glowObjects.size; i++)
		{
			IGlowObjectManager::CGlowObject& object = interfaces::glow->glowObjects[i];

			if (!object.entity || object.IsUnused()) { continue; }

			switch (object.entity->GetClientClass()->classID)
			{
			case CClientClass::CCSPlayer:
				if (!object.entity->IsAlive()) { break; }

				if (object.entity->GetTeam() == globals::localPlayer->GetTeam()) {
					object.SetColor(0.f, 0.f, 1.f);
				}
				else {
					object.SetColor(1.f, 0.f, 0.f);
				}
				break;

			default:
				break;
			}
		}
	}
	return oDoPostScreenSpaceEffects(interfaces::clientMode, pSetup);
}