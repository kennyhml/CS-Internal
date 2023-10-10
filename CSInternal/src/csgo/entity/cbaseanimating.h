#pragma once
#include "cbaseentity.h"

struct CBaseAnimating : public CBaseEntity
{







};

struct CBaseAnimatingOverlay : public CBaseAnimating
{
	NETVAR(Sequence, "CBaseAnimating->m_nSequence", unsigned)
};