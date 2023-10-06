#pragma once
#include "netvar.h"

struct Vec3;
class Weapon;

class CEntity
{
public:
	NETVAR(Spotted, "CBaseEntity->m_bSpotted", bool);
	NETVAR(Dead, "CBasePlayer->deadflag", bool);
	NETVAR(Health, "CBasePlayer->m_iHealth", int32_t);
	NETVAR(Team, "CBaseEntity->m_iTeamNum", int32_t);
	NETVAR(Velocity, "CBasePlayer->m_vecVelocity[0]", Vec3);
	NETVAR(State, "CBasePlayer->m_lifeState", char);
	NETVAR(ActiveWeaponHandle, "CBaseCombatCharacter->m_hActiveWeapon", int32_t);

	int GetActiveIndex()
	{
		return ActiveWeaponHandle() & 0xFFF;
	}
};