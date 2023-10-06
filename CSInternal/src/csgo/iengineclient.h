#pragma once
#include "../util/memory.h"
#include "cvector.h"
#include "cusercmd.h"

class IEngineClient
{
public:
	int GetLocalPlayerIndex()
	{
		return memory::Call<int>(this, 12);
	}

	void SetViewAngles(const CVector& viewAngles)
	{
		memory::Call<void, const CVector&>(this, 19, viewAngles);
	}
};