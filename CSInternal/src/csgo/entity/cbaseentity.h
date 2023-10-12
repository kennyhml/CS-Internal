#pragma once
#include "../../core/netvar.h"
#include "centity.h"

struct CBaseAttributableItem;
struct CCSPlayer;

enum BONES
{
	BONE_HEAD = 6,
	BONE_NECK = 5,
	BONE_SPINE = 2,
	BONE_LEFTSHOULDER = 12,
	BONE_RIGHTSHOULDER = 33,
	BONE_LEFTELBOWROLL = 13,
	BONE_RIGHTELBOWROLL = 34,
	BONE_LEFTHAND = 64,
	BONE_RIGHTHAND = 63,
	BONE_LEFTKNEEROLL = 54,
	BONE_RIGHTKNEEROLL = 58,
	BONE_LEFTFOOT = 55,
	BONE_RIGHTFOOT = 59
};

struct CBaseEntity : public CEntity
{
	NETVAR(Spotted, "CBaseEntity->m_bSpotted", bool);
	NETVAR(OwnerEntity, "CBaseEntity->m_hOwnerEntity", BaseHandle);
	NETVAR(ModelIndex, "CBaseEntity->m_nModelIndex", unsigned);
	NETVAR(SimulationTime, "CBaseEntity->m_flSimulationTime", float);
	NETVAR(Team, "CBaseEntity->m_iTeamNum", int32_t);
	NETVAR(Name, "CBaseEntity->m_iName", int);

	const char* GetClsName()
	{
		return memory::CallVmtFn<const char*>(this, 59);
	}

	int GetIndex()
	{
		return *reinterpret_cast<int*>((uintptr_t)this + 0x64);
	}

	void SetModelIndex(const int index)
	{
		memory::CallVmtFn<void>(this, 75, index);
	}

	int GetTeam()
	{
		return memory::CallVmtFn<int>(this, 88);
	}

	int GetHealth()
	{
		return memory::CallVmtFn<int>(this, 122);
	}

	bool IsAlive()
	{
		return memory::CallVmtFn<bool>(this, 156);
	}

	bool IsPlayer()
	{
		return memory::CallVmtFn<bool>(this, 158);
	}

	bool IsWeapon()
	{
		return memory::CallVmtFn<bool>(this, 166);
	}

	void SetSequence(int sequence)
	{
		memory::CallVmtFn<void>(this, 218, sequence);
	}

	CBaseAttributableItem* GetActiveWeapon()
	{
		return memory::CallVmtFn<CBaseAttributableItem*>(this, 268);
	}

	Vector3 GetEyePosition()
	{
		Vector3 result{ };
		memory::CallVmtFn<void, Vector3&>(this, 285, result);
		return result;
	}

	Vector3 GetAimPunch()
	{
		Vector3 result{ };
		memory::CallVmtFn<void, Vector3&>(this, 346, result);
		return result;
	}

	CCSPlayer* GetObserverTarget()
	{
		return memory::CallVmtFn<CCSPlayer*>(this, 294);
	}

	bool SetupBones(CMatrix3x4* boneToWorldOut, int max, int mask, float time)
	{
		return memory::CallVmtFn<bool>(this + 0x4, 13, boneToWorldOut, max, mask, time);
	}

	bool GetBonePosition(int bone, Vector3& vectorOut, float time)
	{
		CMatrix3x4 bones[128];
		if (!SetupBones(bones, 128, 256, time)) { return false; }

		vectorOut = bones[bone].Origin();
		return true;
	}
};