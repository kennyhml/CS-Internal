#pragma once
#include "cbasecombatweapon.h"

struct CBaseAttributableItem : public CBaseCombatWeapon
{
	NETVAR(AccountID, "CBaseAttributableItem->m_iAccountID", int);
	NETVAR(ItemDefinitionIndex, "CBaseAttributableItem->m_iItemDefinitionIndex", short);
	NETVAR(ItemIDHigh, "CBaseAttributableItem->m_iItemIDHigh", int);
	NETVAR(EntityQuality, "CBaseAttributableItem->m_iEntityQuality", int);
	NETVAR(CustomName, "CBaseAttributableItem->m_szCustomName", char[32]);
	NETVAR(FallbackPaintKit, "CBaseAttributableItem->m_nFallbackPaintKit", unsigned);
	NETVAR(FallbackSeed, "CBaseAttributableItem->m_nFallbackSeed", unsigned);
	NETVAR(FallbackWear, "CBaseAttributableItem->m_flFallbackWear", float);
	NETVAR(FallbackStatTrak, "CBaseAttributableItem->m_nFallbackStatTrak", unsigned);
	NETVAR(OriginalOwnerXuidLow, "CBaseAttributableItem->m_OriginalOwnerXuidLow", int);
	NETVAR(OriginalOwnerXuidHigh, "CBaseAttributableItem->m_OriginalOwnerXuidHigh", int);
};