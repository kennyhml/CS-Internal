#pragma once
#include "../core/netvar.h"

class CWeapon
{
public:
	NETVAR(State, "CBaseCombatWeapon->m_iState", int32_t);
	NETVAR(Clip1Ammo, "CBaseCombatWeapon->m_iClip1", int32_t);
	NETVAR(Clip2Ammo, "CBaseCombatWeapon->m_iClip2", int32_t);
	NETVAR(PrimaryReserveAmmo, "CBaseCombatWeapon->m_iPrimaryReserveAmmoCount", int32_t);
	NETVAR(SecondaryReserveAmmo, "CBaseCombatWeapon->m_iSecondaryReserveAmmoCount", int32_t);
	NETVAR(OwnerHandle, "CBaseCombatWeapon->m_hOwner", int32_t);
};

