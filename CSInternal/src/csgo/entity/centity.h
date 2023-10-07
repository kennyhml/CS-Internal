#pragma once
#include "cunknown.h"
#include "crenderable.h"
#include "cnetworkable.h"
#include "cthinkable.h"
#include "../sound.h"
#include "../../tools/memory.h"

struct MouthInfo;

struct CEntity : public CUnknown, public CRenderable, public CNetworkable, public CThinkable
{
	virtual void Release(void) = 0;
	virtual const Vector3& GetAbsOrigin(void) const = 0;
	virtual const Vector3& GetAbsAngles(void) const = 0;
	virtual MouthInfo* GetMouth(void) = 0;
	virtual bool GetSoundSpatialization(SpatializationInfo& info) = 0;
	virtual bool IsBlurred(void) = 0;

	void SetAbsOrigin(const Vector3& origin)
	{
		using Fn = void(__thiscall*)(void*, const Vector3&);
		static auto SetAbsOrigin = reinterpret_cast<Fn>(memory::offsets::setAbsOrigin);
		SetAbsOrigin(this, origin);
	}

	void SetAbsAngles(const Vector3& angles)
	{
		using Fn = void(__thiscall*)(void*, const Vector3&);
		static auto SetAbsAngles = reinterpret_cast<Fn>(memory::offsets::setAbsAngles);
		SetAbsAngles(this, angles);
	}
};