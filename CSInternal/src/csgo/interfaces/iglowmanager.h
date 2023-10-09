#pragma once
#include "../utlvector.h"

struct CBaseEntity;
struct Vector3;
struct CViewSetup;
struct CMatRenderContextPtr;
struct CEntity;


struct IGlowObjectManager
{
	IGlowObjectManager() { };

	virtual int RegisterGlowObject(CBaseEntity* pEntity, const Vector3& vGlowColor, float flGlowAlpha, bool bRenderWhenOccluded, bool bRenderWhenUnoccluded, int nSplitScreenSlot) = 0;
	virtual void UnregisterGlowObject(int nGlowObjectHandle) = 0;
	virtual void SetEntity(int nGlowObjectHandle, CBaseEntity* pEntity) = 0;
	virtual void SetColor(int nGlowObjectHandle, const Vector3& vGlowColor) = 0;

	virtual void SetAlpha(int nGlowObjectHandle, float flAlpha) = 0;
	virtual void SetRenderFlags(int nGlowObjectHandle, bool bRenderWhenOccluded, bool bRenderWhenUnoccluded) = 0;

	virtual bool IsRenderingWhenOccluded(int nGlowObjectHandle) const = 0;
	virtual bool IsRenderingWhenUnoccluded(int nGlowObjectHandle) const = 0;
	virtual bool HasGlowEffect(CBaseEntity* pEntity) const = 0;

	virtual void RenderGlowEffects(const CViewSetup* pSetup, int nSplitScreenSlot) = 0;

	virtual void RenderGlowModels(const CViewSetup* pSetup, int nSplitScreenSlot, CMatRenderContextPtr& pRenderContext);
	virtual void ApplyEntityGlowEffects(const CViewSetup* pSetup, int nSplitScreenSlot, CMatRenderContextPtr& pRenderContext, float flBloomScale, int x, int y, int w, int h);

	struct CGlowObject
	{
		int nextFreeSlot;
		CEntity* entity;

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