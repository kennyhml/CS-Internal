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
#include "../csgo/interfaces/iglowmanager.h"
#include "../csgo/interfaces/iglobalvarsbase.h"
#include "../csgo/interfaces/ipanel.h"
#include "../csgo/interfaces/ienginevgui.h"
#include "../csgo/interfaces/idebugoverlay.h"
#include "../csgo/interfaces/isurface.h"

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
	inline IGlowObjectManager* glow = nullptr;
	inline IClient* client = nullptr;
	inline IClientMode* clientMode = nullptr;
	inline IGlobalVarsBase* globals = nullptr;
	inline IPanel* panel = nullptr;
	inline IEngineVGui* engineVGui = nullptr;
	inline IDebugOverlay* debugOverlay = nullptr;
	inline ISurface* surface = nullptr;
}
