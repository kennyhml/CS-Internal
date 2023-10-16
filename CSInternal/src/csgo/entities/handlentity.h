#pragma once

struct BaseHandle;

struct HandleEntity
{
	virtual ~HandleEntity() { }
	virtual void SetRefEHandle(const BaseHandle& ref) = 0;
	virtual const BaseHandle& GetRefEHandle() const = 0;
};