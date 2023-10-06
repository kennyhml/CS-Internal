#pragma once
#include "centity.h"

class IClientEntityList
{
public:
	CEntity* GetClientEntityFromIndex(int index)
	{
		return memory::Call<CEntity*>(this, 3, index);
	}

	CEntity* GetClientEntityFromHandle(int handle)
	{
		return memory::Call<CEntity*>(this, 4, handle);
	}

	int NumberOfEntities(bool includeNonNetworkable)
	{
		return memory::Call<int>(this, 5, includeNonNetworkable);
	}

};