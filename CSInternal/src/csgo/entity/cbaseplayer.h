#pragma once
#include "cbasecombatcharacter.h"


enum CPlayerFlag : uint32_t
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_WATERJUMP = (1 << 2),
	FL_ONTRAIN = (1 << 3),
	FL_INRAIN = (1 << 4),
	FL_FROZEN = (1 << 5),
	FL_ATCONTROLS = (1 << 6),
	FL_CLIENT = (1 << 7),
	FL_FAKECLIENT = (1 << 8),
};

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
	NETVAR(Fov, "CBasePlayer->m_iFOV", int32_t);
	NETVAR(ObserverMode, "CBasePlayer->m_iObserverMode", int32_t);
	NETVAR(Ducked, "CBasePlayer->m_bDucked", bool);

};