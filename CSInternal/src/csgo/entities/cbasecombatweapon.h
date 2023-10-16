#pragma once
#include "cbaseentity.h"

struct CBaseCombatWeapon : public CBaseEntity
{
	NETVAR(State, "CBaseCombatWeapon->m_iState", int32_t);
	NETVAR(AmmoClip1, "CBaseCombatWeapon->m_iClip1", int);
	NETVAR(AmmoClip2, "CBaseCombatWeapon->m_iClip2", int);
	NETVAR(PrimaryReserveAmmo, "CBaseCombatWeapon->m_iPrimaryReserveAmmoCount", int);
	NETVAR(SecondaryReserveAmmo, "CBaseCombatWeapon->m_iSecondaryReserveAmmoCount", int);

	NETVAR(ViewModelIndex, "CBaseCombatWeapon->m_iViewModelIndex", int);
	NETVAR(WorldModelIndex, "CBaseCombatWeapon->m_iWorldModelIndex", int);
	NETVAR(WorldDroppedModelIndex, "CBaseCombatWeapon->m_iWorldDroppedModelIndex", int);
	NETVAR(WeaponWorldModel, "CBaseCombatWeapon->m_hWeaponWorldModel", int);
};