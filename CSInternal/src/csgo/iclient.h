#pragma once
#include "datatable.h"
#include "../tools/memory.h"

class IClient
{
public:
	ClientClass* GetAllClasses()
	{
		return memory::Call<ClientClass*>(this, 8);

	}
};