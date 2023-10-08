#pragma once
#include "../../tools/memory.h"

struct CStudioHdr;
struct CRenderable;
struct CMatrix3x4;
struct Vector3;

struct CDrawModelInfo
{
	CStudioHdr* studioHdr;
	void* hardwareData;
	int32_t decals;
	int32_t skin;
	int32_t body;
	int32_t hitboxSet;
	CRenderable* renderable;
};

struct IMaterial;

struct IStudioRender
{
	enum
	{
		STUDIORENDER_DRAW_ENTIRE_MODEL = 0,
		STUDIORENDER_DRAW_OPAQUE_ONLY = 0x01,
		STUDIORENDER_DRAW_TRANSLUCENT_ONLY = 0x02,
		STUDIORENDER_DRAW_GROUP_MASK = 0x03,
		STUDIORENDER_DRAW_NO_FLEXES = 0x04,
		STUDIORENDER_DRAW_STATIC_LIGHTING = 0x08,
		STUDIORENDER_DRAW_ACCURATETIME = 0x10,
		STUDIORENDER_DRAW_NO_SHADOWS = 0x20,
		STUDIORENDER_DRAW_GET_PERF_STATS = 0x40,
		STUDIORENDER_DRAW_WIREFRAME = 0x80,
		STUDIORENDER_DRAW_ITEM_BLINK = 0x100,
		STUDIORENDER_SHADOWDEPTHTEXTURE = 0x200,
		STUDIORENDER_UNUSED = 0x400,
		STUDIORENDER_SKIP_DECALS = 0x800,
		STUDIORENDER_MODEL_IS_CACHEABLE = 0x1000,
		STUDIORENDER_SHADOWDEPTHTEXTURE_INCLUDE_TRANSLUCENT_MATERIALS = 0x2000,
		STUDIORENDER_NO_PRIMARY_DRAW = 0x4000,
		STUDIORENDER_SSAODEPTHTEXTURE = 0x8000,
	};

	enum EOverrideType : std::int32_t
	{
		OVERRIDE_NORMAL = 0,
		OVERRIDE_BUILD_SHADOWS,
		OVERRIDE_DEPTH_WRITE,
		OVERRIDE_SELECTIVE,
		OVERRIDE_SSAO_DEPTH_WRITE,
	};

	virtual void DrawModel(void*, void*, CDrawModelInfo&, CMatrix3x4*, float*, float*, float*, const Vector3&, int) = 0;

	void SetColorModulation(float* color)
	{
		memory::CallVmtFn<void>(this, 27, color);
	}

	void SetAlphaModulation(float alpha)
	{
		memory::CallVmtFn<void>(this, 28, alpha);
	}

	void ForcedMaterialOverride(IMaterial* material, int type = OVERRIDE_NORMAL, int index = -1)
	{
		memory::CallVmtFn<void>(this, 33, material, type, index);
	}

	bool IsForcedMaterialOverride()
	{
		return memory::CallVmtFn<bool>(this, 34);
	}
};