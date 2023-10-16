#pragma once
#include "cbasecombatweapon.h"
#include "../../tools/memory.h"
#include <unordered_map>

struct AttributeManager_t;

enum ItemDefinitionIndex
{
	WEAPON_INVALID = -1,
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5 = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SHIELD,
	WEAPON_SCAR20,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_SNOWBALL,
	WEAPON_BUMPMINE,
	WEAPON_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA = 5035
};

inline std::unordered_map<ItemDefinitionIndex, const char*> knifeModels
{
	{ItemDefinitionIndex::WEAPON_KNIFE, "models/weapons/v_knife_default_ct.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_T, "models/weapons/v_knife_default_t.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_FLIP, "models/weapons/v_knife_flip.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_FLIP, "models/weapons/v_knife_flip.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_GUT, "models/weapons/v_knife_gut.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT, "models/weapons/v_knife_karam.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET, "models/weapons/v_knife_m9_bay.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL, "models/weapons/v_knife_tactical.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_FALCHION, "models/weapons/v_knife_falchion_advanced.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_SURVIVAL_BOWIE, "models/weapons/v_knife_survival_bowie.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY, "models/weapons/v_knife_butterfly.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_FALCHION, "models/weapons/v_knife_falchion_advanced.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_PUSH, "models/weapons/v_knife_push.mdl"},
	{ItemDefinitionIndex::WEAPON_BAYONET, "models/weapons/v_knife_bayonet.mdl"},
};

enum SkinIDs : int32_t
{
	RED_LAMINATE_AK = 14,
	CASE_HARDENED_AK = 44,
	SAFARI_MESH_AK = 72,
	PREDATOR_AK = 170,
	REDLINE_AK = 282,
	ELITE_BUILD_AK = 422,
};

struct CBaseAttributableItem : public CBaseCombatWeapon
{
	NETVAR(AccountID, "CBaseAttributableItem->m_iAccountID", int);
	NETVAR(ItemDefinitionIndex, "CBaseAttributableItem->m_iItemDefinitionIndex", short);
	NETVAR(ItemIDHigh, "CBaseAttributableItem->m_iItemIDHigh", int);
	NETVAR(ItemIDLow, "CBaseAttributableItem->m_iItemIDLow", int);
	NETVAR(EntityQuality, "CBaseAttributableItem->m_iEntityQuality", int);
	NETVAR(CustomName, "CBaseAttributableItem->m_szCustomName", char[32]);
	NETVAR(FallbackPaintKit, "CBaseAttributableItem->m_nFallbackPaintKit", uint32_t);
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