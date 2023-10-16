#pragma once
#include "../hacks.h"
#include "../interfaces.h"
#include "../../csgo/entities/cplayerinfo.h"
#include "../../csgo/entities/cbaseattributableitem.h"
#include <cwchar>
#include <stdio.h>

#define PI 3.14159265359f
const float WIDTH_FACTOR = 0.3f;

void hacks::esp::fonts::Init()
{
	// Text fonts
	textTiny = interfaces::surface->CreateFont_();
	textMedium = interfaces::surface->CreateFont_();
	textBig = interfaces::surface->CreateFont_();
	interfaces::surface->SetFontGlyphSet(textTiny, "Arial", 12, 700, 0, 0, FONTFLAG_DROPSHADOW);
	interfaces::surface->SetFontGlyphSet(textMedium, "Arial", 18, 700, 0, 0, FONTFLAG_DROPSHADOW);
	interfaces::surface->SetFontGlyphSet(textBig, "Arial", 35, 700, 0, 0, FONTFLAG_DROPSHADOW);

	// Weapon icon fonts
	weaponTiny = interfaces::surface->CreateFont_();
	weaponMedium = interfaces::surface->CreateFont_();
	weaponBig = interfaces::surface->CreateFont_();
	interfaces::surface->SetFontGlyphSet(weaponTiny, "Counter-Strike", 18, 700, 0, 0, FONTFLAG_ANTIALIAS);
	interfaces::surface->SetFontGlyphSet(weaponMedium, "Counter-Strike", 30, 700, 0, 0, FONTFLAG_ANTIALIAS);
	interfaces::surface->SetFontGlyphSet(weaponBig, "Counter-Strike", 50, 700, 0, 0, FONTFLAG_ANTIALIAS);
}

HFont hacks::esp::GetTextFont(float targetDistance)
{
	if (targetDistance < 350) { return fonts::textBig; }
	else if (targetDistance < 700) { return fonts::textMedium; }
	else { return fonts::textTiny; }
}

HFont hacks::esp::GetWeaponFont(float targetDistance)
{
	if (targetDistance < 350) { return fonts::weaponBig; }
	else if (targetDistance < 700) { return fonts::weaponMedium; }
	else { return fonts::weaponTiny; }
}

const wchar_t* hacks::esp::GetWeaponIcon(int32_t weaponID)
{
	switch (weaponID)
	{
	case CClientClass::CWeaponHKP2000:
		return L"A";
	case CClientClass::CAK47:
		return L"B";
	case CClientClass::CWeaponGlock:
		return L"C";
	case CClientClass::CWeaponMP9: // not sure here
		return L"D";
	case CClientClass::CWeaponAug:
		return L"E";
	case CClientClass::CDEagle:
		return L"F";
	case CClientClass::CSmokeGrenade:
		return L"G";
	case CClientClass::CHEGrenade:
		return L"H";
	case CClientClass::CWeaponG3SG1:
		return L"I";
	case CClientClass::CKnife:
	case CClientClass::CKnifeGG:
		return L"J";
	case CClientClass::CWeaponXM1014:
		return L"K";
	case CClientClass::CWeaponMAC10:
		return L"L";
	case CClientClass::CWeaponP90:
		return L"M";
	case CClientClass::CWeaponAWP:
		return L"N";
	case CClientClass::CWeaponSCAR20:
		return L"O";
	case CClientClass::CFlashbang: // not sure 
		return L"P";
	case CClientClass::CWeaponUMP45:
		return L"Q";
	case 999: // not sure , awp too?
		return L"R";
	case 1000: // dual barretas
		return L"S";
	case CClientClass::CWeaponFamas:
		return L"T";
	case CClientClass::CWeaponFiveSeven:
		return L"U";
	case CClientClass::CWeaponGalil:
	case CClientClass::CWeaponGalilAR:
		return L"V";
	case CClientClass::CWeaponM4A1:
		return L"W";
	case CClientClass::CWeaponMP5Navy:
		return L"X";
	case 1001: // CWeaponHKP2000?
		return L"Y";
	case 1002: // irgendwas fettes?
		return L"Z";
	case CClientClass::CC4:
		return L"a";
	default:
		return L"???";
	}
}

void hacks::esp::DrawName(const char* name, Rect box, float distance)
{
	int textWidth;
	int textHeight;

	wchar_t wideCharArray[128];
	size_t converted = mbstowcs_s(NULL, wideCharArray, sizeof(wideCharArray) / sizeof(wideCharArray[0]), name, _TRUNCATE);
	const wchar_t* wname = wideCharArray;

	HFont font = GetTextFont(distance);
	interfaces::surface->GetTextSize(font, wname, textWidth, textHeight);

	float rectCenterX = box.x + (box.w / 2);
	float textX = rectCenterX - (textWidth / 2);
	float textY = box.y - textHeight;

	interfaces::surface->DrawSetTextColor(255, 0, 0, 255);
	interfaces::surface->DrawSetTextFont(font);
	interfaces::surface->DrawSetTextPos(textX, textY);
	interfaces::surface->DrawPrintText(wname, std::wcslen(wname));
}

void hacks::esp::DrawWeapon(int weaponID, Rect box, float distance)
{
	int textWidth;
	int textHeight;
	const wchar_t* weaponIcon = GetWeaponIcon(weaponID);

	HFont font = GetWeaponFont(distance);
	interfaces::surface->GetTextSize(font, weaponIcon, textWidth, textHeight);

	float rectCenterX = box.x + (box.w / 2);
	float textX = rectCenterX - (textWidth / 2);
	float textY = box.y + box.h + 2;

	interfaces::surface->DrawSetTextColor(255, 255, 255);
	interfaces::surface->DrawSetTextFont(font);
	interfaces::surface->DrawSetTextPos(textX, textY);
	interfaces::surface->DrawPrintText(weaponIcon, std::wcslen(weaponIcon));
}

void hacks::esp::DrawHealth(int health, Rect box)
{
	// Make the health bar 1/40th of the width of the box
	float width = box.w * 0.025f;
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

bool hacks::esp::ShouldDrawEntity(CCSPlayer* entity)
{
	return (entity && entity->IsAlive() && entity->IsPlayer() && !entity->IsDormant()
		&& entity->GetTeam() != globals::localPlayer->GetTeam()
		&& !(globals::localPlayer->IsDead()
			&& globals::localPlayer->GetObserverTarget() == entity));
}

hacks::esp::Rect hacks::esp::GetBoundingRect(const Vector3& top, const Vector3& bottom)
{
	float height = bottom.y - top.y;
	// The width is the distance from the center x to the right / left x,
	// so the conventional 'width' would actually be width x 2
	float width = height * WIDTH_FACTOR;
	return Rect{ top.x - width, top.y, width * 2, height };
}

void hacks::esp::Run(uintptr_t panel)
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

		auto weapon = entity->GetActiveWeapon();
		if (!weapon) { continue; } // player might have died
		auto id = static_cast<CClientClass::ClassID>(weapon->GetClientClass()->classID);

		DrawName(info.name, rect, distance);
		DrawWeapon(id, rect, distance);
		DrawHealth(entity->GetHealth(), rect);


	}
}

