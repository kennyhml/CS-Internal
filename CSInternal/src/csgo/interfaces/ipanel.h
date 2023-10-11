#pragma once
#include "../../tools/memory.h"

struct IPanel
{
	const char* GetName(uint32_t panel) noexcept
	{
		return memory::CallVmtFn<const char*>(this, 36, panel);
	}
};