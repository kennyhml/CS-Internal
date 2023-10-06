#pragma once
#include "../util/memory.h"
#include "../util/netvar.h"

#include "cvector.h"

class CEntity
{
public:
	NETVAR(Spotted, "CBaseEntity->m_bSpotted", bool);
	NETVAR(Dead, "CBasePlayer->deadflag", bool);
	NETVAR(Health, "CBasePlayer->m_iHealth", int32_t);
	NETVAR(Team, "CBaseEntity->m_iTeamNum", int32_t);
	NETVAR(Velocity, "CBasePlayer->m_vecVelocity[0]", CVector);
	NETVAR(State, "CBasePlayer->m_lifeState", char);
	NETVAR(ActiveWeaponHandle, "CBaseCombatCharacter->m_hActiveWeapon", int32_t);

	int GetIndex()
	{
		return *reinterpret_cast<int*>(this + 0x64);
	}

	bool IsEnemy()
	{
		if (!globals::localPlayer) { return false; }
		return Team() != globals::localPlayer->Team();
	}

	bool IsAlive()
	{
		return Health() != 0;
	}

	bool IsPlayer()
	{
		return memory::Call<bool>(this, 158);
	}

	void GetEyePosition(CVector& eyePosOut)
	{
		memory::Call<void, CVector&>(this, 285, eyePosOut);
	}

	void GetAimPunch(CVector& aimPunchOut)
	{
		memory::Call<void, CVector&>(this, 346, aimPunchOut);
	}
};