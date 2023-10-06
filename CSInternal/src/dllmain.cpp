#define WIN32LEAN_AND_MEAN
#include <Windows.h>
#include "interfaces.h"
#include <iostream>
#include "geometry.h"
#include "weapon.h"

FILE* fConsole = nullptr;

template <typename T>
T* GetInterface(const char* name, const char* moduleName)
{
	HMODULE handle = GetModuleHandle(moduleName);

	if (!handle) { return nullptr; }

	uintptr_t addr = reinterpret_cast<uintptr_t>(GetProcAddress(handle, "CreateInterface"));
	if (!addr) { return nullptr; }

	using Fn = T * (*)(const char*, int*);
	const auto CreateInterface = reinterpret_cast<Fn>(addr);

	return CreateInterface(name, nullptr);
}

void MainThread(HMODULE instance)
{
	AllocConsole();
	freopen_s(&fConsole, "CONOUT$", "w", stdout);
	std::cout << "DLL injected!\n";

	client = GetInterface<IClient>("VClient018", "client.dll");
	entityList = GetInterface<IEntityList>("VClientEntityList003", "client.dll");

	uintptr_t clientBase = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));

	SetupNetvars();

	while (!GetAsyncKeyState(VK_DELETE) & 1) {
		for (int i = 1; i <= 64; ++i) {

			const auto entity = entityList->GetClientEntity(i);
			if (!entity || entity->Dead()) { continue; }

			int weaponIndex = entity->GetActiveIndex();
			Weapon* weapon = (Weapon*)entityList->GetClientEntityFromHandle(entity->ActiveWeaponHandle());
			std::cout << std::dec << weapon->Clip1Ammo() << std::endl;
		}
	}

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

