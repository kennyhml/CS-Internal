#pragma once
#include "../hacks.h"
#include "../interfaces.h"
#include "../../csgo/entity/cplayerinfo.h"
#include <cwchar>
#include <stdio.h>


#define PI 3.14159265359f

const float WIDTH_FACTOR = 0.3f;

void fonts::Init()
{
	tiny = interfaces::surface->CreateFont_();
	medium = interfaces::surface->CreateFont_();
	big = interfaces::surface->CreateFont_();

	interfaces::surface->SetFontGlyphSet(tiny, "Arial", 12, 700, 0, 0, FONTFLAG_DROPSHADOW);
	interfaces::surface->SetFontGlyphSet(medium, "Arial", 18, 700, 0, 0, FONTFLAG_DROPSHADOW);
	interfaces::surface->SetFontGlyphSet(big, "Arial", 35, 700, 0, 0, FONTFLAG_DROPSHADOW);
}

struct Rect
{
	float x, y, w, h;

};

static HFont GetFont(float distance)
{
	if (distance < 350) { return fonts::big; }
	else if (distance < 700) { return fonts::medium; }
	else { return fonts::tiny; }
}

static void DrawName(const char* name, Rect box, float distance)
{
	int textWidth;
	int textHeight;

	wchar_t wideCharArray[128];
	size_t converted = mbstowcs_s(NULL, wideCharArray, sizeof(wideCharArray) / sizeof(wideCharArray[0]), name, _TRUNCATE);
	const wchar_t* wname = wideCharArray;

	HFont font = GetFont(distance);
	interfaces::surface->GetTextSize(font, wname, textWidth, textHeight);

	float rectCenterX = box.x + (box.w / 2);
	float textX = rectCenterX - (textWidth / 2);
	float textY = box.y - textHeight;

	interfaces::surface->DrawSetTextColor(255, 0, 0, 255);
	interfaces::surface->DrawSetTextFont(font);
	interfaces::surface->DrawSetTextPos(textX, textY);
	interfaces::surface->DrawPrintText(wname, std::wcslen(wname));
}

static void DrawHealth(int health, Rect box)
{
	// Make the health bar 1/20th of the width of the box
	float width = box.w * 0.05f;
	float healthX = box.x - width;

	interfaces::surface->DrawSetColor(255, 0, 0);

	float pixelPerHealth = box.h / 100.f;
	float takenHpHeight = (100 - health) * pixelPerHealth;
	if (takenHpHeight >= 1.f)
	{
		interfaces::surface->DrawFilledRect(healthX, box.y, healthX + width, box.y + takenHpHeight);
	}

	interfaces::surface->DrawSetColor(0, 255, 0);

	float hpHeight = box.h - takenHpHeight;
	interfaces::surface->DrawFilledRect(healthX, box.y + takenHpHeight, healthX + width, box.y + box.h);
}

static bool ShouldDrawEntity(CCSPlayer* entity)
{
	return (entity && entity->IsAlive() && entity->IsPlayer() && !entity->IsDormant()
		&& entity->GetTeam() != globals::localPlayer->GetTeam()
		&& !(globals::localPlayer->IsDead()
			&& globals::localPlayer->GetObserverTarget() == entity));
}

static Rect GetBoundingRect(const Vector3& top, const Vector3& bottom)
{
	float height = bottom.y - top.y;
	// The width is the distance from the center x to the right / left x,
	// so the conventional 'width' would actually be width x 2
	float width = height * WIDTH_FACTOR;
	return Rect{ top.x - width, top.y, width * 2, height };
}

void hacks::Esp(uintptr_t panel)
{
	// We wanna use the tool panel to draw cause its always available
	if (panel != interfaces::engineVGui->GetPanel(PANEL_TOOLS)
		|| !globals::localPlayer || !interfaces::engine->IsInGame()) {
		return;
	}

	int w;
	int h;
	interfaces::engine->GetScreenSize(w, h);
	interfaces::surface->DrawSetColor(0, 0, 0, 255);

	float radAimbotFov = (float)(20.f * PI / 180);
	float radViewFov = (float)(110 * PI / 180);

	float circleRadius = tanf(radAimbotFov / 2) / tanf(radViewFov / 2) * w;

	interfaces::surface->DrawOutlinedCircle(w / 2, h / 2, circleRadius, 100);

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

		float distance = entity->GetAbsOrigin().DistTo(globals::localPlayer->GetAbsOrigin());
		auto rect = GetBoundingRect(top, feet);

		interfaces::surface->DrawSetColor(255, 255, 255, 255);
		interfaces::surface->DrawOutlinedRect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
		interfaces::surface->DrawLine(w / 2, h, feet.x, feet.y);

		DrawName(info.name, rect, distance);
		DrawHealth(entity->GetHealth(), rect);
	}
}



