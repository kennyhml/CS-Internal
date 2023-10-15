#include "../hacks.h"
#include "../interfaces.h"
#include "../../csgo/entity/cplayerinfo.h"
#include "../../csgo/entity/cbaseviewmodel.h"
#include <unordered_map>

std::unordered_map<ItemDefinitionIndex, const char*> knifeModels
{
	{ItemDefinitionIndex::WEAPON_KNIFE, "models/weapons/v_knife_default_ct.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_T, "models/weapons/v_knife_default_t.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_FLIP, "models/weapons/v_knife_flip.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_FLIP, "models/weapons/v_knife_flip.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_GUT, "models/weapons/v_knife_gut.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT, "models/weapons/v_knife_karam.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET, "models/weapons/v_knife_m9_bay.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL, "models/weapons/v_knife_tactical.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_FALCHION, "models/weapons/v_knife_falchion_advanced.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_SURVIVAL_BOWIE, "models/weapons/v_knife_survival_bowie.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY, "models/weapons/v_knife_butterfly.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_FALCHION, "models/weapons/v_knife_falchion_advanced.mdl"},
	{ItemDefinitionIndex::WEAPON_KNIFE_PUSH, "models/weapons/v_knife_push.mdl"},
	{ItemDefinitionIndex::WEAPON_BAYONET, "models/weapons/v_knife_bayonet.mdl"},
};

hacks::skins::Skin hacks::skins::GetWeaponSkin(int32_t weaponID)
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

void ChangeKnifeModel(CBaseAttributableItem* knife)
{
	int viewModelHandle = globals::localPlayer->ViewModelHandle();
	auto viewModel = interfaces::entityList->FromHandle<CBaseViewModel*>(viewModelHandle);
	auto targetModelID = ItemDefinitionIndex::WEAPON_KNIFE_FALCHION;

	int targetModelIndex = interfaces::modelInfo->GetModelIndex(knifeModels[targetModelID]);
	if (targetModelIndex == -1) { std::cout << "Invalid knife model index!\n"; }

	if (!viewModel || viewModel->ModelIndex() == targetModelIndex) { return; }

	std::cout << "[+] Need to update knife model!\n";
	viewModel->ModelIndex() = targetModelIndex;
	knife->ViewModelIndex() = targetModelIndex;
	knife->ItemDefinitionIndex() = targetModelID;

	knife->WorldModelIndex() = targetModelIndex + 1;
	knife->ModelIndex() = targetModelIndex;
	std::cout << "[+] Knife model updated!\n";
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

