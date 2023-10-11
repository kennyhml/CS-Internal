#pragma once
#include "../hacks.h"
#include "../interfaces.h"
#include "../../csgo/entity/cplayerinfo.h"

static bool ShouldDrawEntity(CCSPlayer* entity)
{
	return (entity && entity->IsAlive() && entity->IsPlayer()
		&& entity->GetTeam() != globals::localPlayer->GetTeam()
		&& !(globals::localPlayer->IsDead()
			&& globals::localPlayer->GetObserverTarget() == entity));
}

void hacks::Esp(uintptr_t panel)
{
	// We wanna use the tool panel to draw cause its always available
	if (panel != interfaces::engineVGui->GetPanel(PANEL_TOOLS)
		|| !globals::localPlayer || !interfaces::engine->IsInGame()) {
		return;
	}

	for (int i = 0; i < interfaces::globals->maxClients; i++)
	{
		auto entity = interfaces::entityList->FromIndex<CCSPlayer*>(i);

		if (!ShouldDrawEntity(entity)) { continue; }

		CPlayerInfo info;
		interfaces::engine->GetPlayerInfo(entity->GetIndex(), &info);

		CMatrix3x4 bones[128];
		if (!entity->SetupBones(bones, 128, 256, interfaces::globals->currentTime)) { continue; }

		Vector3 top;
		Vector3 headPos = bones[8].Origin() + Vector3{ 0.f, 0.f, 11.f };
		if (interfaces::debugOverlay->ScreenPosition(headPos, top)) { continue; }

		Vector3 feet;
		Vector3 feetPos = entity->GetAbsOrigin() - Vector3{ 0.f, 0.f, 9.f };
		if (interfaces::debugOverlay->ScreenPosition(feetPos, feet)) { continue; }

		float height = feet.y - top.y;
		float width = height * 0.3f;

		int left = top.x - width;
		int right = top.x + width;

		interfaces::surface->DrawSetColor(255, 255, 255, 255);
		interfaces::surface->DrawOutlinedRect(left, top.y, right, feet.y);
	}

}



