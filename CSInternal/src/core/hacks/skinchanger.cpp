#include "../hacks.h"
#include "../interfaces.h"
#include "../../csgo/entity/cbaseattributableitem.h"

typedef void (*ForceUpdate)(void);

static int GetWeaponPaint(int32_t weaponID)
{
	switch (weaponID)
	{
	case CClientClass::CDEagle:
		return 711;
	case CClientClass::CAK47:
		return 44;
	case CClientClass::CWeaponAWP:
		return 38;
	default:
		return 0;
	}
}

void hacks::ChangeSkins()
{
	if (!globals::localPlayer || !globals::localPlayer->IsAlive()
		|| !interfaces::engine->IsInGame()) {
		return;
	}
	auto weapons = globals::localPlayer->Weapons();

	for (auto weaponHandle : weapons)
	{
		auto weapon = interfaces::entityList->FromHandle<CBaseAttributableItem*>(weaponHandle);
		if (!weapon) { continue; }

		int paint = GetWeaponPaint(weapon->GetClientClass()->classID);
		if (!paint) { continue; } // no paint known for that weapon

		bool needUpdate = weapon->FallbackPaintKit() != paint;

		weapon->ItemIDHigh() = -1;
		weapon->FallbackPaintKit() = paint;
		weapon->FallbackWear() = 0.f;

		if (needUpdate) {
			static auto FullUpdate = reinterpret_cast<ForceUpdate>(memory::FindPattern(memory::signatures::forceUpdate));
			FullUpdate();
		}
	}
}

