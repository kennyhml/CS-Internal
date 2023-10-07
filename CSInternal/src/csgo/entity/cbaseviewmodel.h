#pragma once
#include "cbaseentity.h"

struct CBaseViewModel : public CBaseEntity
{
	NETVAR(Owner, "CBaseViewModel->m_hOwner", BaseHandle);
	NETVAR(Weapon, "CBaseViewModel->m_hWeapon", BaseHandle);
};