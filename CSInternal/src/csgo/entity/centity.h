#pragma once
#include "cunknown.h"
#include "crenderable.h"
#include "cnetworkable.h"
#include "cthinkable.h"
#include "../sound.h"

struct MouthInfo;

struct CEntity : public CUnknown, public CRenderable, public CNetworkable, public CThinkable
{
public:
	virtual void Release(void) = 0;

	virtual const Vector3& GetAbsOrigin(void) const = 0;
	virtual const Vector3& GetAbsAngles(void) const = 0;

	virtual MouthInfo* GetMouth(void) = 0;

	virtual bool GetSoundSpatialization(SpatializationInfo& info) = 0;

	virtual bool IsBlurred(void) = 0;

	void SetAbsOrigin(Vector3 origin)
	{
		using Fn = void(__thiscall*)(void*, const Vector3&);
		static auto SetAbsOriginFn = reinterpret_cast<Fn>(m::sigs.setAbsOrigin);
		SetAbsOriginFn(this, origin);
	}

	void SetAbsAngles(Vector3 view)
	{
		using Fn = void(__thiscall*)(void*, const Vector3&);
		static auto SetAbsAnglesFn = reinterpret_cast<Fn>(m::sigs.setAbsAngles);
		SetAbsAnglesFn(this, view);
	}
};