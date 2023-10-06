#pragma once
#include "../util/memory.h"
#include "cvector.h"
#include "cusercmd.h"
#include "cplayerinfo.h"

class IEngineClient
{
public:

	bool IsInGame()
	{
		return memory::Call<bool>(this, 27);
	}

	bool GetPlayerInfo(int playerIndex, CPlayerInfo* infoOut)
	{
		return memory::Call<bool>(this, 8, playerIndex, infoOut);
	}

	int GetLocalPlayerIndex()
	{
		return memory::Call<int>(this, 12);
	}

	void SetViewAngles(const CVector& viewAngles)
	{
		memory::Call<void, const CVector&>(this, 19, viewAngles);
	}
};
