#pragma once
#include "cbaseentity.h"

struct CBaseViewModel : public CBaseEntity
{
	NETVAR(Owner, "CBaseViewModel->m_hOwner", int32_t);
	NETVAR(Weapon, "CBaseViewModel->m_hWeapon", int32_t);
	NETVAR(ModelIndex, "CBaseViewModel->m_nModelIndex", int32_t);
	NETVAR(ViewModelIndex, "CBaseViewModel->m_nViewModelIndex", int32_t);
};