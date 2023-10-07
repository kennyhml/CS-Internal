#pragma once
#include "../tools/memory.h"
#include "../core/netvar.h"

#include "vector.h"

// class gbbb
// {
// public:
// 	NETVAR(Spotted, "CBaseEntity->m_bSpotted", bool);
// 	NETVAR(Dead, "CBasePlayer->deadflag", bool);
// 	NETVAR(Health, "CBasePlayer->m_iHealth", int32_t);
// 	NETVAR(Team, "CBaseEntity->m_iTeamNum", int32_t);
// 	NETVAR(Velocity, "CBasePlayer->m_vecVelocity[0]", Vector3);
// 	NETVAR(State, "CBasePlayer->m_lifeState", char);
// 	NETVAR(ActiveWeaponHandle, "CBaseCombatCharacter->m_hActiveWeapon", int32_t);
// 
// 	int GetIndex()
// 	{
// 		return *reinterpret_cast<int*>(this + 0x64);
// 	}
// 
// 	bool IsEnemy()
// 	{
// 		if (!globals::localPlayer) { return false; }
// 		return Team() != globals::localPlayer->Team();
// 	}
// 
// 	bool IsAlive()
// 	{
// 		return Health() != 0;
// 	}
// 
// 	bool IsPlayer()
// 	{
// 		return memory::Call<bool>(this, 158);
// 	}
// 
// 	void GetEyePosition(Vector3& eyePosOut)
// 	{
// 		memory::Call<void, Vector3&>(this, 285, eyePosOut);
// 	}
// 
// 	void GetAimPunch(Vector3& aimPunchOut)
// 	{
// 		memory::Call<void, Vector3&>(this, 346, aimPunchOut);
// 	}
// };