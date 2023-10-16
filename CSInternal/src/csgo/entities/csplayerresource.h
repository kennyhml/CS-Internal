#pragma once
#include "cbaseentity.h"

struct CCSPlayerResource : public CBaseEntity
{
	NETVAR(PlayerC4, "CCSPlayerResource->m_iPlayerC4", int);
	NETVAR(PlayerVIP, "CCSPlayerResource->m_iPlayerVIP", int);
	NETVAR(BombsiteCenterA, "CCSPlayerResource->m_bombsiteCenterA", Vector3);
	NETVAR(BombsiteCenterB, "CCSPlayerResource->m_bombsiteCenterB", Vector3);
};