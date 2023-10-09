#pragma once
#include "../utlvector.h"

struct CBaseEntity;
struct Vector3;
struct CViewSetup;
struct CMatRenderContextPtr;
struct CEntity;


struct IGlowObjectManager
{
	struct CGlowObject
	{
		int nextFreeSlot;
		CBaseEntity* entity;

		struct
		{
			float r;
			float g;
			float b;
			float a;
		} color;

		bool glowAlphaCappedByRenderAlpha;
		float glowAlphaFunctionOfMaxVelocity;
		float glowAlphaMax;
		float glowPulseOverdrive;

		bool renderWhenOccluded;
		bool renderWhenUnoccluded;

		bool fullBloomRender;
		int fullBloomStencilTestValue;
		int glowStyle;
		int splitScreenSlot;

		static constexpr int END_OF_FREE_LIST = -1;
		static constexpr int ENTRY_IN_USE = -2;

		bool IsUnused() const { return nextFreeSlot != CGlowObject::ENTRY_IN_USE; }

		void SetColor(float r, float g, float b, float a = 1.f)
		{
			color = { r, g, b, a };
			renderWhenOccluded = true;
			renderWhenUnoccluded = false;
		}
	};

	UtlVector<CGlowObject> glowObjects;
};