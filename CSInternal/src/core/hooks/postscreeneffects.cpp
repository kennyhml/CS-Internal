#include "../hooks.h"

static bool IsEnemy(CBaseEntity* entity)
{
	return entity->GetTeam() != globals::localPlayer->GetTeam();
}

static void SetGlowColor(IGlowObjectManager::CGlowObject& object)
{
	auto entity = object.entity;
	auto id = static_cast<CClientClass::ClassID>(entity->GetClientClass()->classID);

	switch (id)
	{
	case CClientClass::CCSPlayer:
		if (!entity->IsAlive()) { return; }
		object.SetColor(IsEnemy(entity) ? Color{ 1.f, 0.f, 0.f } : Color{ 0.f, 0.f, 1.f });
		break;

		// C4
	case CClientClass::CC4:
	case CClientClass::CPlantedC4:
		object.SetColor(1.f, 1.f, 1.f);
		break;

		// Grenades
	case CClientClass::CDecoyProjectile:
		break; // dont draw decoys at all

	case CClientClass::CSmokeGrenadeProjectile:
	case CClientClass::CMolotovProjectile:
	case CClientClass::CFlashbang:
	case CClientClass::CBaseCSGrenadeProjectile:
		object.SetColor(1.f, 1.f, 0.f);
		break;

	default:
		break;
	}
}

bool __stdcall hooks::DoPostScreenSpaceEffects(const CViewSetup* pSetup)
{
	if (globals::localPlayer && interfaces::engine->IsInGame())
	{
		for (int i = 0; i < interfaces::glow->glowObjects.Count(); i++)
		{
			IGlowObjectManager::CGlowObject& object = interfaces::glow->glowObjects[i];

			if (!object.entity || object.IsUnused()) { continue; }
			SetGlowColor(object);
		}
	}
	return oDoPostScreenSpaceEffects(interfaces::clientMode, pSetup);
}