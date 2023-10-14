#include "../hacks.h"
#include "../interfaces.h"
#include "../../csgo/entity/cbaseattributableitem.h"
#include "../../csgo/entity/cplayerinfo.h"

static bool ShouldEqualizeAimPunch()
{
	int weapon = globals::localPlayer->GetActiveWeapon()->GetClientClass()->classID;

	switch (weapon) {
	case CClientClass::CWeaponAWP:
	case CClientClass::CWeaponUSP:
	case CClientClass::CWeaponHKP2000:
	case CClientClass::CWeaponP250:
	case CClientClass::CWeaponGlock:
		return false;

	default:
		return true;
	}
}

static bool IsValidTarget(CCSPlayer* entity)
{
	return (entity && entity->IsAlive() && !entity->IsDormant()
		&& entity->GetTeam() != globals::localPlayer->GetTeam());
}

static Vector3 GetAngleToEnemy(CUserCmd* cmd, CMatrix3x4* bones, Vector3& aimPunch, Vector3& eyePos)
{
	Vector3 result{};
	CTrace trace;
	interfaces::trace->TraceRay(
		CRay{ eyePos, bones[8].Origin() },
		MASK_SHOT,
		CTraceFilter{ globals::localPlayer },
		trace
	);

	bool goodFraction = trace.fraction >= 0.95f;
	if (trace.entity && goodFraction) {
		result = Vector3{ (bones[8].Origin() - eyePos).ToAngle() - (cmd->viewAngles + aimPunch) };
	}
	return result;
}

static Vector3 FindBestAngle(CUserCmd* cmd)
{
	float bestFov = 20.f;
	Vector3 bestAngle{};

	Vector3 eyePos = globals::localPlayer->GetEyePosition();
	Vector3 aimPunch{};
	if (ShouldEqualizeAimPunch()) {
		Vector3 aimPunch = globals::localPlayer->GetAimPunch();
	}

	for (int i = 0; i <= interfaces::globals->maxClients; i++)
	{
		auto entity = interfaces::entityList->FromIndex<CCSPlayer*>(i);
		if (!IsValidTarget(entity)) { continue; }

		CPlayerInfo info;
		interfaces::engine->GetPlayerInfo(entity->GetIndex(), &info);

		CMatrix3x4 bones[128];
		if (!entity->SetupBones(bones, 128, 256, interfaces::globals->currentTime)) { continue; }

		Vector3 angle = GetAngleToEnemy(cmd, bones, aimPunch, eyePos);
		if (!(angle.x || angle.y || angle.z)) { continue; }

		float angleFov = hypot(angle.x, angle.y);
		if (angleFov < bestFov) {
			bestFov = angleFov;
			bestAngle = angle;
		}
	}
	return bestAngle;
}

void hacks::Aimbot(CUserCmd* cmd)
{
	if (!(cmd->buttons & IN_ATTACK) || !globals::localPlayer->IsAlive()) { return; }

	auto currentWeapon = globals::localPlayer->GetActiveWeapon();
	auto weaponID = currentWeapon->GetClientClass()->classID;

	if (!currentWeapon->AmmoClip1() || (weaponID == CClientClass::CWeaponAWP
		&& !globals::localPlayer->IsScoped() || globals::localPlayer->IsWalking())) {
		return;
	}

	Vector3 bestAngle = FindBestAngle(cmd);
	cmd->viewAngles = cmd->viewAngles + bestAngle;
}

