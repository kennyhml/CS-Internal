#pragma once
#include "cbasebflex.h"
#include <array>

struct CBaseCombatCharacter : public CBaseFlex
{
	NETVAR(Weapons, "CBaseCombatCharacter->m_hMyWeapons", std::array<uintptr_t, 8>);
	NETVAR(ActiveWeapon, "CBaseCombatCharacter->m_hActiveWeapon", int32_t)

};