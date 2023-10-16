#pragma once
#include "../entities/centity.h"

struct IClientEntityList
{
	CEntity* GetClientEntityFromIndex(int index)
	{
		return memory::CallVmtFn<CEntity*>(this, 3, index);
	}

	template <typename Type>
	Type FromIndex(int index)
	{
		return reinterpret_cast<Type>(GetClientEntityFromIndex(index));
	}

	CEntity* GetClientEntityFromHandle(int handle)
	{
		return memory::CallVmtFn<CEntity*>(this, 4, handle);
	}

	template <typename Type>
	Type FromHandle(int handle)
	{
		return reinterpret_cast<Type>(GetClientEntityFromHandle(handle));
	}

	int NumberOfEntities(bool includeNonNetworkable)
	{
		return memory::CallVmtFn<int>(this, 5, includeNonNetworkable);
	}

	int GetHighestEntityIndex()
	{
		return memory::CallVmtFn<int>(this, 6);
	}

};
