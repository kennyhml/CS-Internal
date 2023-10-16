#pragma once
#include "cbaseplayer.h"

struct CCSPlayer : public CBasePlayer
{
	NETVAR(IsScoped, "CCSPlayer->m_bIsScoped", bool);
	NETVAR(CanMoveDuringFreezePeriod, "CCSPlayer->m_bCanMoveDuringFreezePeriod", bool);
	NETVAR(IsWalking, "CCSPlayer->m_bIsWalking", bool);
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
	NETVAR(IsStrafing, "CCSPlayer->m_bStrafing", bool);
	NETVAR(MatchKills, "CCSPlayer->m_iMatchStats_Kills", int32_t);
	NETVAR(MatchDamage, "CCSPlayer->m_iMatchStats_Damage", int32_t);
	NETVAR(MatchEnemiesFlashed, "CCSPlayer->m_iMatchStats_EnemiesFlashed", int32_t);
	NETVAR(MoveState, "CCSPlayer->m_iMoveState", int32_t);
	NETVAR(LookingAtWeapon, "CCSPlayer->m_bIsLookingAtWeapon", bool);
	NETVAR(IsHoldingLookAtWeapon, "CCSPlayer->m_bIsHoldingLookAtWeapon", bool);
};