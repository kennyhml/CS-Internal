#pragma once
#include "../../tools/memory.h"
#include "../vector.h"

struct CPlayerInfo;

struct IEngineClient
{
	const CMatrix4x4& WorldToScreenMatrix() noexcept
	{
		return memory::CallVmtFn<const CMatrix4x4&>(this, 37);
	}

	void GetScreenSize(int32_t& width, int32_t& height) noexcept
	{
		memory::CallVmtFn<void, int32_t&, int32_t&>(this, 5, width, height);
	}

	bool IsInGame()
	{
		return memory::CallVmtFn<bool>(this, 27);
	}

	bool GetPlayerInfo(int playerIndex, CPlayerInfo* infoOut)
	{
		return memory::CallVmtFn<bool>(this, 8, playerIndex, infoOut);
	}

	int GetLocalPlayerIndex()
	{
		return memory::CallVmtFn<int>(this, 12);
	}

	Vector3 GetViewAngles()
	{
		Vector3 result{};
		memory::CallVmtFn<void, Vector3&>(this, 18, result);
		return result;
	}

	void SetViewAngles(const Vector3& viewAngles)
	{
		memory::CallVmtFn<void, const Vector3&>(this, 19, viewAngles);
	}

	void ExecuteClientCommand(const char* command)
	{
		memory::CallVmtFn<void>(this, 108, command, 2);
	}

};
