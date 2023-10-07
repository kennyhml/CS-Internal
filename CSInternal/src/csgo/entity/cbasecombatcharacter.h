#pragma once
#include "cbasebflex.h"

struct CBaseCombatCharacter : public CBaseFlex
{
	NETVAR(Weapons, "CBaseCombatCharacter->m_hMyWeapons", std::array<uintptr_t, 48>);
	NETVAR(ActiveWeapon, "CBaseCombatCharacter->m_hActiveWeapon", int32_t)
};