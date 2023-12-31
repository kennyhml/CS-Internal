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

	Vector3& GetAbsOrigin()
	{
		return memory::CallVmtFn<Vector3&>(this, 10);
	}

};