#pragma once
#include "cbaseplayer.h"

struct CCSPlayer : public CBasePlayer
{
	NETVAR(IsScoped, "CCSPlayer->m_bIsScoped", bool);
	NETVAR(IsDefusing, "CCSPlayer->m_bIsDefusing", bool);
	NETVAR(HasGunGameImmunity, "CCSPlayer->m_bGunGameImmunity", bool);
	NETVAR(Account, "CCSPlayer->m_iAccount", int);
	NETVAR(InBombZone, "CCSPlayer->m_bInBombZone", bool);
	NETVAR(HasDefuser, "CCSPlayer->m_bHasDefuser", bool);
	NETVAR(HasHelmet, "CCSPlayer->m_bHasHelmet", bool);
	NETVAR(HasHeavyArmor, "CCSPlayer->m_bHasHeavyArmor", bool);
	NETVAR(ShotsFired, "CCSPlayer->m_iShotsFired", int32_t);
	NETVAR(EyeAngles, "CCSPlayer->m_angEyeAngles[0]", Vector2);
	NETVAR(InBuyZone, "CCSPlayer->m_bInBuyZone", bool);
	NETVAR(ArmorValue, "CCSPlayer->m_ArmorValue", int32_t);
	NETVAR(HasNightVision, "CCSPlayer->m_bHasNightVision", bool);
	NETVAR(FlashDuration, "CCSPlayer->m_flFlashDuration", float);
	NETVAR(Strafing, "CCSPlayer->m_bStrafing", bool);
};