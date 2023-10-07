#pragma once
#include "cbasecombatcharacter.h"

struct CBasePlayer : public CBaseCombatCharacter
{
	NETVAR(Flags, "CBasePlayer->m_fFlags", int);
	NETVAR(Velocity, "CBasePlayer->m_vecVelocity[0]", Vector3);
	NETVAR(ViewModel, "CBasePlayer->m_hViewModel[0]", BaseHandle);
	NETVAR(ViewOffset, "CBasePlayer->m_vecViewOffset[0]", Vector3);
	NETVAR(TickBase, "CBasePlayer->m_nTickBase", int);
	NETVAR(IsDead, "CBasePlayer->deadflag", bool);
	NETVAR(Health, "CBasePlayer->m_iHealth", int32_t);
	NETVAR(State, "CBasePlayer->m_lifeState", char);
	NETVAR(Fov, "CBasePlayer->m_iFOV", uint32_t);

};