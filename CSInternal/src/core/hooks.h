#pragma once
#include "interfaces.h"
#include "hacks.h"

struct CUserCmd;

namespace hooks
{
	void Init();
	void Destroy();

	using CreateMoveFn = bool(__thiscall*)(void*, float, CUserCmd*);
	inline CreateMoveFn oCreateMove = nullptr;
	bool __stdcall CreateMove(float frameTime, CUserCmd* cmd);

	using DrawModelFn = void(__thiscall*)(void*, void*, CDrawModelInfo&, CMatrix3x4*, float*, float*, Vector3&, int);
	inline DrawModelFn oDrawModel = nullptr;
	void __stdcall DrawModel(
		void* result,
		CDrawModelInfo& info,
		CMatrix3x4* bones,
		float* flexWeights,
		float* flexDelayedWeights,
		Vector3& modelOrigin,
		int flags);

	using DoPostScreenSpaceEffectsFn = bool(__thiscall*)(void* _this, const CViewSetup* pSetup);
	inline DoPostScreenSpaceEffectsFn oDoPostScreenSpaceEffects = nullptr;
	bool __stdcall DoPostScreenSpaceEffects(const CViewSetup* pSetup);
}

