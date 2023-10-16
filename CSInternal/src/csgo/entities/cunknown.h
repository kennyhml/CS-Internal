#pragma once
#include "handlentity.h"

struct Collideable;
struct CNetworkable;
struct CRenderable;
struct CEntity;
struct CBaseEntity;
struct CThinkable;
struct CAlphaProperty;

struct CUnknown : public HandleEntity
{
	virtual Collideable* GetCollideable() = 0;
	virtual CNetworkable* GetClientNetworkable() = 0;
	virtual CRenderable* GetClientRenderable() = 0;
	virtual CEntity* GetClientEntity() = 0;
	virtual CBaseEntity* GetBaseEntity() = 0;
	virtual CThinkable* GetClientThinkable() = 0;
	virtual CAlphaProperty* GetClientAlphaProperty() = 0;
};