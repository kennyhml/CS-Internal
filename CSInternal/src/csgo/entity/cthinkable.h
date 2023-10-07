#pragma once

struct CUnknown;

struct CThinkable
{
	virtual CUnknown* GetClientUnknown() = 0;
	virtual void ClientThink() = 0;
	virtual void* GetThinkHandle() = 0;
	virtual void SetThinkHandle(int think) = 0;
	virtual void Release() = 0;
};