#pragma once
#include <cstdint>

struct IGlobalVarsBase
{
	float realTime;
	int32_t frameCount;
	float absFrameTime;
	float absFrameStartTime;
	float currentTime;
	float frameTime;
	int32_t maxClients;
	int32_t tickCount;
	float intervalPerTick;
	float interpolationAmount;
	int32_t frameSimulationTicks;
	int32_t networkProtocol;
	void* saveData;
	bool client;
	bool remoteClient;
	int32_t timestampNetworkingBase;
	int32_t timestampRandomizeWindow;
};