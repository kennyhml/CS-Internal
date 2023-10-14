#include "../hacks.h"
#include "../interfaces.h"
#include "../../csgo/entity/cbaseattributableitem.h"
#include "../../csgo/entity/cplayerinfo.h"

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

void ForceUpdateWeapon(CBaseAttributableItem* weapon)
{
	weapon->CustomMaterialInitialized() = (weapon->FallbackPaintKit() <= 0);
	weapon->CustomMaterials().clear();

	weapon->PostDataUpdate(DataUpdateType::DATA_UPDATE_CREATED);
	weapon->OnDataChanged(DataUpdateType::DATA_UPDATE_CREATED);
}

void hacks::ChangeSkins()
{
	if (!interfaces::engine->IsInGame()
		|| !globals::localPlayer
		|| !globals::localPlayer->IsAlive()) {
		return;
	}

	auto weapons = globals::localPlayer->Weapons();
	bool anyUpdated = false;

	for (auto weaponHandle : weapons)
	{
		auto weapon = interfaces::entityList->FromHandle<CBaseAttributableItem*>(weaponHandle);
		if (!weapon) { continue; }

		int paint = GetWeaponPaint(weapon->GetClientClass()->classID);
		if (!paint) { continue; } // no paint known for that weapon

		if (weapon->FallbackPaintKit() == paint) { continue; };

		weapon->ItemIDHigh() = -1;
		weapon->FallbackPaintKit() = paint;
		weapon->FallbackWear() = 0.f;

		ForceUpdateWeapon(weapon);
	}
}

