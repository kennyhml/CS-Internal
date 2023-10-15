#include "../hacks.h"
#include "../interfaces.h"
#include "../../csgo/entity/cbaseattributableitem.h"
#include "../../csgo/entity/cplayerinfo.h"
#include "../../csgo/entity/cbaseviewmodel.h"

int hacks::skins::GetWeaponPaint(int32_t weaponID)
{
	switch (weaponID)
	{
	case CClientClass::CDEagle:
		return 711;
	case CClientClass::CAK47:
		return 44;
	case CClientClass::CWeaponAWP:
		return 38;
	case CClientClass::CKnife:
		return 44;

	default:
		return 0;
	}
}

void hacks::skins::ForceUpdateWeapon(CBaseAttributableItem* weapon)
{
	weapon->CustomMaterialInitialized() = (weapon->FallbackPaintKit() <= 0);
	weapon->CustomMaterials().clear();

	weapon->PostDataUpdate(DataUpdateType::DATA_UPDATE_CREATED);
	weapon->OnDataChanged(DataUpdateType::DATA_UPDATE_CREATED);
}

void hacks::skins::Change()
{
	if (!interfaces::engine->IsInGame()
		|| !globals::localPlayer
		|| !globals::localPlayer->IsAlive()) {
		return;
	}

	CPlayerInfo myInfo;
	interfaces::engine->GetPlayerInfo(globals::localPlayer->GetIndex(), &myInfo);

	auto weapons = globals::localPlayer->Weapons();
	auto viewModel = interfaces::entityList->FromHandle<CBaseViewModel*>(globals::localPlayer->ViewModelHandle());

	bool anyUpdated = false;

	for (auto weaponHandle : weapons)
	{
		auto weapon = interfaces::entityList->FromHandle<CBaseAttributableItem*>(weaponHandle);
		if (!weapon) { continue; }

		auto classID = weapon->GetClientClass()->classID;

		int paint = GetWeaponPaint(classID);
		if (!paint) { continue; } // no paint known for that weapon

		int butterfly = interfaces::modelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
		if (classID == CClientClass::CKnife && viewModel && viewModel->ModelIndex() != butterfly && weaponHandle == globals::localPlayer->ActiveWeapon())
		{
			std::cout << "Knife updated!\n";
			weapon->ItemDefinitionIndex() = 507;
			viewModel->ModelIndex() = butterfly;
			weapon->WorldModelIndex() = butterfly + 1;
			weapon->ModelIndex() = butterfly;
			weapon->ViewModelIndex() = butterfly;
		}

		if (weapon->FallbackPaintKit() == paint) { continue; };

		std::cout << weapon->GetClientClass()->networkName << " needs to be updated!\n";

		weapon->ItemIDHigh() = -1;
		weapon->FallbackPaintKit() = paint;
		weapon->FallbackWear() = 0.f;

		weapon->OriginalOwnerXuidLow() = myInfo.xuidLow;
		ForceUpdateWeapon(weapon);
	}
}

