#pragma once
#include "entity/centity.h"

struct IClientEntityList
{
	CEntity* GetClientEntityFromIndex(int index)
	{
		return memory::Call<CEntity*>(this, 3, index);
	}

	template <typename Type>
	Type FromIndex(int index)
	{
		return reinterpret_cast<Type>(GetClientEntityFromIndex(index));
	}

	CEntity* GetClientEntityFromHandle(int handle)
	{
		return memory::Call<CEntity*>(this, 4, handle);
	}

	template <typename Type>
	Type FromHandle(int handle)
	{
		return reinterpret_cast<Type>(GetClientEntityFromHandle(handle));
	}

	int NumberOfEntities(bool includeNonNetworkable)
	{
		return memory::Call<int>(this, 5, includeNonNetworkable);
	}

	int GetHighestEntityIndex()
	{
		return memory::Call<int>(this, 6);
	}

};
