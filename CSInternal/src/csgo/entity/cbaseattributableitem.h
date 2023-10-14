#pragma once
#include "cbasecombatweapon.h"
#include "../../tools/memory.h"

struct AttributeManager_t;

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
	NETVAR(AttributeManager, "CBaseAttributableItem->m_AttributeManager", AttributeManager_t*);

	bool& CustomMaterialInitialized()
	{
		static int32_t offset = *reinterpret_cast<int32_t*>(memory::FindPattern(memory::signatures::customMatInit));
		return *reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	UtlVector<IRefCounted*> CustomMaterials()
	{
		static int32_t offset = *reinterpret_cast<int32_t*>(memory::FindPattern(memory::signatures::customMats)) - 12;
		return *reinterpret_cast<UtlVector<IRefCounted*>*>(reinterpret_cast<uintptr_t>(this) + offset);
	}
};