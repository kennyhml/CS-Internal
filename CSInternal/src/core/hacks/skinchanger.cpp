#include "../hacks.h"
#include "../interfaces.h"
#include "../../csgo/entities/cbaseviewmodel.h"

hacks::skins::Skin hacks::skins::GetWeaponSkin(int32_t weaponID)
{
	switch (weaponID)
	{
	case CClientClass::CDEagle:
		return 711;
	case CClientClass::CAK47:
		return SkinIDs::REDLINE_AK;
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
	weapon->CustomMaterials().RemoveAll();

	weapon->PostDataUpdate(DataUpdateType::DATA_UPDATE_CREATED);
	weapon->OnDataChanged(DataUpdateType::DATA_UPDATE_CREATED);
}

void hacks::skins::ChangeKnifeModel(CBaseAttributableItem* knife)
{
	int viewModelHandle = globals::localPlayer->ViewModelHandle();
	auto viewModel = interfaces::entityList->FromHandle<CBaseViewModel*>(viewModelHandle);
	auto targetModelID = ItemDefinitionIndex::WEAPON_KNIFE_FALCHION;

	int targetModelIndex = interfaces::modelInfo->GetModelIndex(knifeModels[targetModelID]);
	if (targetModelIndex == -1) { std::cout << "Invalid knife model index!\n"; }

	if (!viewModel || viewModel->ModelIndex() == targetModelIndex) { return; }

	std::cout << "[+] Knife model needs to be updated...";
	viewModel->ModelIndex() = targetModelIndex;
	knife->ViewModelIndex() = targetModelIndex;
	knife->ItemDefinitionIndex() = targetModelID;

	knife->WorldModelIndex() = targetModelIndex + 1;
	knife->ModelIndex() = targetModelIndex;
	std::cout << "done!" << std::endl;
}

bool hacks::skins::SetSkin(CBaseAttributableItem* weapon, Skin skin)
{
	if (weapon->FallbackPaintKit() == skin) { return false; };

	// -1 forces the weapon to use the fallback stats
	weapon->ItemIDHigh() = -1;
	weapon->FallbackPaintKit() = skin;

	// float from 0 to 1 determining how worn down the weapon looks.
	weapon->FallbackWear() = 0.f;
	return true;
}

void hacks::skins::Change()
{
	if (!interfaces::engine->IsInGame()
		|| !globals::localPlayer
		|| !globals::localPlayer->IsAlive()) {
		return;
	}

	auto weapons = globals::localPlayer->Weapons();

	for (auto weaponHandle : weapons)
	{
		auto weapon = interfaces::entityList->FromHandle<CBaseAttributableItem*>(weaponHandle);
		if (!weapon) { continue; }

		int classID = weapon->GetClientClass()->classID;
		int skinToApply = GetWeaponSkin(classID);
		if (!skinToApply) { continue; }

		// changing the knife model, only do it when active otherwise the color derps out
		if (classID == CClientClass::CKnife) {
			if (weaponHandle != globals::localPlayer->ActiveWeapon()) { continue; }
			ChangeKnifeModel(weapon);
		}

		if (SetSkin(weapon, skinToApply)) {
			ForceUpdateWeapon(weapon);
		}
	}
}

