#pragma once
#include "../../tools/memory.h"

struct ClientClass;

struct IClient
{
	ClientClass* GetAllClasses()
	{
		return memory::CallVmtFn<ClientClass*>(this, 8);
	}
};