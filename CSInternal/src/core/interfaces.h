#pragma once
#include "globals.h"
#include "../csgo/interfaces/icliententitylist.h"
#include "../csgo/interfaces/iengineclient.h"
#include "../csgo/interfaces/ienginetraceclient.h"
#include "../csgo/interfaces/iclient.h"
#include "../csgo/interfaces/iweaponsystem.h"
#include "../csgo/interfaces/iclientmode.h"
#include "../csgo/interfaces/istudiorender.h"
#include "../csgo/interfaces/imaterialsystem.h"

namespace interfaces
{
	void Init();

	template <typename T>
	T* GetInterface(const char* name, const char* moduleName);

	inline IClientEntityList* entityList = nullptr;
	inline IEngineClient* engine = nullptr;
	inline IEngineTraceClient* trace = nullptr;
	inline IWeaponSystem* weapons = nullptr;
	inline IStudioRender* render = nullptr;
	inline IMaterialSystem* materialSystem = nullptr;

	inline IClient* client = nullptr;
	inline IClientMode* clientMode = nullptr;
}
