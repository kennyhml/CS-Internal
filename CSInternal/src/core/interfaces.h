#pragma once
#include "globals.h"

#include "../csgo/icliententitylist.h"
#include "../csgo/iengineclient.h"
#include "../csgo/ienginetraceclient.h"
#include "../csgo/iclient.h"


namespace interfaces
{
	void Init();

	template <typename T>
	T* GetInterface(const char* name, const char* moduleName);

	inline IClientEntityList* entityList = nullptr;
	inline IEngineClient* engine = nullptr;
	inline IEngineTraceClient* trace = nullptr;

	inline IClient* client = nullptr;
	inline void* clientMode = nullptr;
}
