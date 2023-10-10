#include "../hooks.h"

bool __stdcall hooks::DoPostScreenSpaceEffects(const CViewSetup* pSetup)
{
	if (globals::localPlayer && interfaces::engine->IsInGame())
	{
		for (int i = 0; i < interfaces::glow->glowObjects.size; i++)
		{
			IGlowObjectManager::CGlowObject& object = interfaces::glow->glowObjects[i];

			if (!object.entity || object.IsUnused()) { continue; }

			switch (object.entity->GetClientClass()->classID)
			{
			case CClientClass::CCSPlayer:
				if (!object.entity->IsAlive()) { break; }

				if (object.entity->GetTeam() == globals::localPlayer->GetTeam()) {
					object.SetColor(0.f, 0.f, 1.f);
				}
				else {
					object.SetColor(1.f, 0.f, 0.f);
				}
				break;

			default:
				break;
			}
		}
	}
	return oDoPostScreenSpaceEffects(interfaces::clientMode, pSetup);
}