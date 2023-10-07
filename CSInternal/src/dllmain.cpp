#define WIN32LEAN_AND_MEAN
#include <Windows.h>
#include "core/interfaces.h"
#include <iostream>
#include "geometry.h"
#include "csgo/cweapon.h"
#include "core/hooks.h"

FILE* fConsole = nullptr;

void MainThread(HMODULE instance)
{
	AllocConsole();
	freopen_s(&fConsole, "CONOUT$", "w", stdout);
	std::cout << "DLL injected!\n";

	interfaces::Init();
	SetupNetvars();
	hooks::Init();

	globals::localPlayer = reinterpret_cast<CSPlayer*>(interfaces::entityList->GetClientEntityFromIndex(interfaces::engine->GetLocalPlayerIndex()));

	while (!GetAsyncKeyState(VK_DELETE) & 1) {
		for (int i = 1; i <= 64; ++i) {

			const auto entity = reinterpret_cast<CSPlayer*>(interfaces::entityList->GetClientEntityFromIndex(i));
			if (!entity
				|| entity->IsDead()
				|| entity->GetTeam() == globals::localPlayer->GetTeam()
				|| !entity->IsPlayer()) {
				continue;
			}

			std::cout << entity->GetHealth() << "\n";

		}
	}

	hooks::Destroy();
	if (fConsole) { fclose(fConsole); }
	FreeConsole();
	FreeLibraryAndExitThread(instance, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		HANDLE hThread = CreateThread(
			nullptr,
			0,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread),
			hModule,
			NULL,
			nullptr);
		return hThread ? CloseHandle(hThread) : FALSE;
	}

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

