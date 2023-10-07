#pragma once
#include "centity.h"
#include "../../core/netvar.h"
#include <array>

struct BaseAttributableItem;
struct CSPlayer;

struct BaseEntity : public CEntity
{
	NETVAR(Spotted, "CBaseEntity->m_bSpotted", bool);
	NETVAR(OwnerEntity, "CBaseEntity->m_hOwnerEntity", BaseHandle);
	NETVAR(ModelIndex, "CBaseEntity->m_nModelIndex", unsigned);
	NETVAR(SimulationTime, "CBaseEntity->m_flSimulationTime", float);

	const char* GetClassName()
	{
		return memory::Call<const char*>(this, 59);
	}

	void SetModelIndex(const int index)
	{
		memory::Call<void>(this, 75, index);
	}

	int GetTeam()
	{
		return memory::Call<int>(this, 88);
	}

	int GetHealth()
	{
		return memory::Call<int>(this, 122);
	}

	bool IsAlive()
	{
		return memory::Call<bool>(this, 156);
	}

	bool IsPlayer()
	{
		return memory::Call<bool>(this, 158);
	}

	bool IsWeapon()
	{
		return memory::Call<bool>(this, 166);
	}

	void SetSequence(int sequence)
	{
		memory::Call<void>(this, 218, sequence);
	}

	BaseAttributableItem* GetActiveWeapon()
	{
		return memory::Call<BaseAttributableItem*>(this, 268);
	}

	Vector3 GetEyePosition()
	{
		Vector3 result{ };
		memory::Call<void, Vector3&>(this, 285, result);
		return result;
	}

	Vector3 GetAimPunch()
	{
		Vector3 result{ };
		memory::Call<void, Vector3&>(this, 346, result);
		return result;
	}

	CSPlayer* GetObserverTarget()
	{
		return memory::Call<CSPlayer*>(this, 294);
	}

	Matrix3x4* GetBoneMatrix();
	Vector3 GetBonePosition(int bone);
};

struct BaseAnimating : public BaseEntity {};

struct BaseAnimatingOverlay : public BaseAnimating
{
	NETVAR(Sequence, "CBaseAnimating->m_nSequence", unsigned)
};

struct BaseFlex : public BaseAnimatingOverlay {};

struct BaseCombatCharacter : public BaseFlex
{
	NETVAR(Weapons, "CBaseCombatCharacter->m_hMyWeapons", std::array<uintptr_t, 48>);
};

struct BasePlayer : public BaseCombatCharacter
{
	NETVAR(Flags, "CBasePlayer->m_fFlags", int);
	NETVAR(Velocity, "CBasePlayer->m_vecVelocity[0]", Vector3);
	NETVAR(ViewModel, "CBasePlayer->m_hViewModel[0]", BaseHandle);
	NETVAR(TickBase, "CBasePlayer->m_nTickBase", int);
	NETVAR(IsDead, "CBasePlayer->deadflag", bool);
};

struct CSPlayer : public BasePlayer
{
	NETVAR(IsScoped, "CCSPlayer->m_bIsScoped", bool);
	NETVAR(IsDefusing, "CCSPlayer->m_bIsDefusing", bool);
	NETVAR(HasGunGameImmunity, "CCSPlayer->m_bGunGameImmunity", bool);
	NETVAR(Account, "CCSPlayer->m_iAccount", int);
	NETVAR(InBombZone, "CCSPlayer->m_bInBombZone", bool);
	NETVAR(HasDefuser, "CCSPlayer->m_bHasDefuser", bool);
	NETVAR(HasHelmet, "CCSPlayer->m_bHasHelmet", bool);
};

struct CSPlayerResource : public BaseEntity
{
	NETVAR(PlayerC4, "CCSPlayerResource->m_iPlayerC4", int);
	NETVAR(PlayerVIP, "CCSPlayerResource->m_iPlayerVIP", int);
	NETVAR(BombsiteCenterA, "CCSPlayerResource->m_bombsiteCenterA", Vector3);
	NETVAR(BombsiteCenterB, "CCSPlayerResource->m_bombsiteCenterB", Vector3);
};

struct BaseCombatWeapon : public BaseEntity
{
	NETVAR(ViewModelIndex, "CBaseCombatWeapon->m_iViewModelIndex", int);
	NETVAR(WorldModelIndex, "CBaseCombatWeapon->m_iWorldModelIndex", int);
	NETVAR(WorldDroppedModelIndex, "CBaseCombatWeapon->m_iWorldDroppedModelIndex", int);
	NETVAR(WeaponWorldModel, "CBaseCombatWeapon->m_hWeaponWorldModel", BaseHandle);
};

struct BaseAttributableItem : public BaseCombatWeapon
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
};

struct BaseViewModel : public BaseEntity
{
	NETVAR(Owner, "CBaseViewModel->m_hOwner", BaseHandle);
	NETVAR(Weapon, "CBaseViewModel->m_hWeapon", BaseHandle);
};

struct BaseWeaponWorldModel : public BaseEntity {};