#pragma once
#include "../tools/memory.h"
#include "vector.h"
#include "cusercmd.h"
#include "entity/cplayerinfo.h"

struct IEngineClient
{
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

	void SetViewAngles(const Vector3& viewAngles)
	{
		memory::Call<void, const Vector3&>(this, 19, viewAngles);
	}
};
