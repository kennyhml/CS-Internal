#pragma once
#include "entity.h"
#include "datatable.h"

class IEntityList
{
private:
	virtual void fn0() = 0;
	virtual void fn1() = 0;
	virtual void fn2() = 0;
public:
	virtual CEntity* GetClientEntity(int index) = 0;
	virtual CEntity* GetClientEntityFromHandle(int hEnt) = 0;
	virtual int	NumberOfEntities(bool bIncludeNonNetworkable) = 0;
};

class IClient
{
private:
	virtual void fn0() = 0;
	virtual void fn1() = 0;
	virtual void fn2() = 0;
	virtual void fn3() = 0;
	virtual void fn4() = 0;
	virtual void fn5() = 0;
	virtual void fn6() = 0;
	virtual void fn7() = 0;
public:
	virtual ClientClass* GetAllClasses(void) = 0;
};

inline IEntityList* entityList = nullptr;
inline IClient* client = nullptr;