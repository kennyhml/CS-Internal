#pragma once
#include "../../tools/memory.h"
#include "../vector.h"

struct CEntity;
struct CBaseEntity;

struct CRay
{
	CRay(const Vector3& src, const Vector3& dst) noexcept
	{
		start = src;
		delta = dst - src;
		isSwept = delta.x || delta.y || delta.z;
	}

private:
	Vector3 start;
	char pad0[4]{ };
	Vector3 delta;
	char pad1[40]{ };
	bool isRay{ true };
	bool isSwept;
};

struct CTraceFilter
{
	CTraceFilter(const CEntity* entity) noexcept
	{
		skip = entity;
	}

	virtual bool ShouldHit(CEntity* entity, std::int32_t mask)
	{
		return entity != skip;
	}

	virtual std::int32_t GetTraceType() const
	{
		return 0;
	}

	const CEntity* skip;
};

struct CTrace
{
	Vector3 start;
	Vector3 end;
	char pad[20];
	float fraction;
	int contents;
	unsigned short dispFlags;
	bool allSolid;
	bool startSolid;
	char pad1[4];
	struct Surface_t {
		const char* name;
		short surfaceProps;
		unsigned short flags;
	} surface;
	int hitgroup;
	char pad2[4];
	CBaseEntity* entity;
	char bigPad[4];
};

// https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/mp/src/public/engine/IEngineTrace.h#L148
struct IEngineTraceClient
{
	void TraceRay(
		const CRay& ray,
		const std::uintptr_t mask,
		const CTraceFilter& filter,
		CTrace& trace)
	{
		return memory::CallVmtFn<void, const CRay&, const std::uintptr_t, const CTraceFilter&, CTrace&>(
			this,
			5,
			ray,
			mask,
			filter,
			trace
		);
	}
};