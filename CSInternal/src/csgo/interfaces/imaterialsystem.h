#pragma once
#include "../../tools/memory.h"

struct IMaterial
{
	enum EMaterialVarFlag : int32_t
	{
		IGNOREZ = 1 << 15,
		WIREFRAME = 1 << 28
	};

	void SetMaterialVarFlag(int32_t flag, bool on)
	{
		memory::CallVmtFn<void>(this, 29, flag, on);
	}
};

struct IMaterialSystem
{
	IMaterial* FindMaterial(const char* name)
	{
		return memory::CallVmtFn<IMaterial*>(this, 84, name, nullptr, true, nullptr);
	}
};