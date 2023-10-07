#pragma once

enum ShouldTransmitState : int
{
	SHOULDTRANSMIT_START = 0,
	SHOULDTRANSMIT_END
};

enum DataUpdateType : int
{
	DATA_UPDATE_CREATED = 0,
	DATA_UPDATE_DATATABLE_CHANGED,
	DATA_UPDATE_POST_UPDATE,
};

struct bf_read;
struct CUnknown;
struct CClass;

struct CNetworkable
{
	virtual CUnknown* GetClientUnknown() = 0;

	virtual void Release() = 0;

	virtual CClass* GetClientClass() = 0;

	virtual void NotifyShouldTransmit(ShouldTransmitState state) = 0;

	virtual void OnPreDataChanged(DataUpdateType updateType) = 0;
	virtual void OnDataChanged(DataUpdateType updateType) = 0;

	virtual void PreDataUpdate(DataUpdateType updateType) = 0;
	virtual void PostDataUpdate(DataUpdateType updateType) = 0;
	virtual void OnDataUnchangedInPVS() = 0;

	virtual bool IsDormant(void) const = 0;

	virtual int Index(void) const = 0;

	virtual void ReceiveMessage(int classID, bf_read& msg) = 0;

	virtual void* GetDataTableBasePtr() = 0;

	virtual void SetDestroyedOnRecreateEntities(void) = 0;
};