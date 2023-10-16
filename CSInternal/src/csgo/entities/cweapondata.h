#pragma once
#include <memory>

enum WeaponType : int
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL = 1,
	WEAPONTYPE_SUBMACHINEGUN = 2,
	WEAPONTYPE_RIFLE = 3,
	WEAPONTYPE_SHOTGUN = 4,
	WEAPONTYPE_SNIPER = 5,
	WEAPONTYPE_MACHINEGUN = 6,
	WEAPONTYPE_C4 = 7,
	WEAPONTYPE_PLACEHOLDER = 8,
	WEAPONTYPE_GRENADE = 9,
	WEAPONTYPE_HEALTHSHOT = 11,
	WEAPONTYPE_FISTS = 12,
	WEAPONTYPE_BREACHCHARGE = 13,
	WEAPONTYPE_BUMPMINE = 14,
	WEAPONTYPE_TABLET = 15,
	WEAPONTYPE_MELEE = 16
};

struct CWeaponData
{
	union
	{
		DEFINE_MEMBER_N(int, maxClip1, 0x14);
		DEFINE_MEMBER_N(int, maxClip2, 0x18);
		DEFINE_MEMBER_N(int, defaultClip1, 0x1C);
		DEFINE_MEMBER_N(int, defaultClip2, 0x20);
		DEFINE_MEMBER_N(int, primaryMaxReserveAmmo, 0x24);
		DEFINE_MEMBER_N(int, secondaryMaxReserveAmmo, 0x28);
		DEFINE_MEMBER_N(char*, worldModel, 0x2C);
		DEFINE_MEMBER_N(char*, viewModel, 0x30);
		DEFINE_MEMBER_N(char*, droppedModel, 0x34);
		DEFINE_MEMBER_N(char*, hudName, 0x88);
		DEFINE_MEMBER_N(char*, viewModel, 0x30);
		DEFINE_MEMBER_N(char*, viewModel, 0x30);
		DEFINE_MEMBER_N(char*, weaponName, 0x8C);

		DEFINE_MEMBER_N(bool, isMeleeWeapon, 0x92);
		DEFINE_MEMBER_N(float, weight, 0x9C);
		DEFINE_MEMBER_N(int, type, 0xC8);
		DEFINE_MEMBER_N(int, price, 0xD0);
		DEFINE_MEMBER_N(int, killAward, 0xD4);
		DEFINE_MEMBER_N(float, cycleTime, 0xDC);
		DEFINE_MEMBER_N(float, cycleTimeAlt, 0xE0);
		DEFINE_MEMBER_N(bool, fullAuto, 0xEC);
		DEFINE_MEMBER_N(int, damage, 0xF0);
		DEFINE_MEMBER_N(float, armorRatio, 0xF4);
		DEFINE_MEMBER_N(int, bullets, 0xF8);
		DEFINE_MEMBER_N(float, penetration, 0xFC);
		DEFINE_MEMBER_N(float, range, 0x108);
		DEFINE_MEMBER_N(float, rangeModifier, 0x10C);
		DEFINE_MEMBER_N(float, throwVelocity, 0x11C);
		DEFINE_MEMBER_N(bool, hasSilencer, 0x120);
		DEFINE_MEMBER_N(char*, bulletType, 0x12C);
		DEFINE_MEMBER_N(float, maxSpeed, 0x130);
		DEFINE_MEMBER_N(float, maxSpeedAlt, 0x134);
		DEFINE_MEMBER_N(float, spread, 0x138);
		DEFINE_MEMBER_N(float, spreadAlt, 0x13C);
		DEFINE_MEMBER_N(int, recoilSeed, 0x184);
	};
};