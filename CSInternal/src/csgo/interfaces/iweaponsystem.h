#pragma once

struct CWeaponData;

struct IWeaponSystem
{
	virtual void fn1() = 0;
	virtual void fn2() = 0;
	virtual const CWeaponData* GetWeaponData(short index) = 0;
};