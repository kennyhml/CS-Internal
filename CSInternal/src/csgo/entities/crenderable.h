#pragma once
#include <stdint.h>
#include "../matrix.h"

struct Model;
struct CUnknown;

enum ModelDataCategory
{
	MODEL_DATA_LIGHTING_MODEL,	// data type returned is a RenderableLightingModel_t
	MODEL_DATA_STENCIL,			// data type returned is a ShaderStencilState_t
	MODEL_DATA_CATEGORY_COUNT,
};

enum ShadowType
{
	SHADOWS_NONE = 0,
	SHADOWS_SIMPLE,
	SHADOWS_RENDER_TO_TEXTURE,
	SHADOWS_RENDER_TO_TEXTURE_DYNAMIC,	// the shadow is always changing state
	SHADOWS_RENDER_TO_DEPTH_TEXTURE,
	SHADOWS_RENDER_TO_TEXTURE_DYNAMIC_CUSTOM,	// changing, and entity uses custom rendering code for shadow
};

struct CModelRenderable
{
	virtual bool GetRenderData(void* data, ModelDataCategory category) = 0;
};

struct RenderableInstance
{
	uint8_t m_nAlpha;
};

struct CRenderable
{
	virtual CUnknown* GetClientUnknown() = 0;
	virtual Vector3 const& GetRenderOrigin(void) = 0;
	virtual Vector3 const& GetRenderAngles(void) = 0;
	virtual bool ShouldDraw(void) = 0;
	virtual int GetRenderFlags(void) = 0;
	virtual void Unused(void) const {}
	virtual unsigned short GetShadowHandle() const = 0;
	virtual unsigned short& RenderHandle() = 0;
	virtual const Model* GetModel() const = 0;
	virtual int DrawModel(int flags, const RenderableInstance& instance) = 0;
	virtual int GetBody() = 0;
	virtual void GetColorModulation(float* color) = 0;
	virtual bool LODTest() = 0;
	virtual bool SetupBones(CMatrix3x4* boneToWorldOut, int maxBones, int boneMask, float currentTime) = 0;
	virtual void SetupWeights(const CMatrix3x4* boneToWorld, int flexWeightCount, float* flexWeights, float* flexDelayedWeights) = 0;
	virtual void DoAnimationEvents(void) = 0;
	virtual void* GetPVSNotifyInterface() = 0;
	virtual void GetRenderBounds(Vector3& mins, Vector3& maxs) = 0;
	virtual void GetRenderBoundsWorldspace(Vector3& mins, Vector3& maxs) = 0;
	virtual void GetShadowRenderBounds(Vector3& mins, Vector3& maxs, ShadowType shadowType) = 0;
	virtual bool ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool GetShadowCastDistance(float* dist, ShadowType shadowType) const = 0;
	virtual bool GetShadowCastDirection(Vector3* direction, ShadowType shadowType) const = 0;
	virtual bool IsShadowDirty() = 0;
	virtual void MarkShadowDirty(bool dirty) = 0;

	virtual CRenderable* GetShadowParent() = 0;
	virtual CRenderable* FirstShadowChild() = 0;
	virtual CRenderable* NextShadowPeer() = 0;
	virtual ShadowType ShadowCastType() = 0;

	virtual void Unused2() {}
	virtual void CreateModelInstance() = 0;
	virtual unsigned short GetModelInstance() = 0;
	virtual const CMatrix3x4& RenderableToWorldTransform() = 0;
	virtual int LookupAttachment(const char* attachmentName) = 0;
	virtual	bool GetAttachment(int number, Vector3& origin, Vector3& angles) = 0;
	virtual bool GetAttachment(int number, CMatrix3x4& matrix) = 0;
	virtual bool ComputeLightingOrigin(int attachmentIndex, Vector3 modelLightingCenter, const CMatrix3x4& matrix, Vector3& transformedLightingCenter) = 0;
	virtual float* GetRenderClipPlane(void) = 0;
	virtual int	 GetSkin() = 0;
	virtual void OnThreadedDrawSetup() = 0;
	virtual bool UsesFlexDelayedWeights() = 0;
	virtual void RecordToolMessage() = 0;
	virtual bool ShouldDrawForSplitScreenUser(int nSlot) = 0;
	virtual uint8_t	OverrideAlphaModulation(uint8_t nAlpha) = 0;
	virtual uint8_t	OverrideShadowAlphaModulation(uint8_t nAlpha) = 0;
	virtual CModelRenderable* GetClientModelRenderable() = 0;
};