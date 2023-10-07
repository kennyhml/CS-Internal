#include "interfaces.h"
#include "netvar.h"
#include <ctype.h>
#include <format>

void SetupNetvars()
{
	for (auto clientClass = interfaces::client->GetAllClasses(); clientClass; clientClass = clientClass->next)
	{
		if (clientClass->recvTable) {
			DumpNetvars(clientClass->networkName, clientClass->recvTable);
		}
	}
}

void DumpNetvars(const char* baseClass, RecvTable* table, std::uint32_t offset)
{
	for (int i = 0; i < table->propsCount; i++)
	{
		const auto prop = &table->props[i];
		if (!prop || isdigit(prop->varName[0])) { continue; }

		if (hash::Hash(prop->varName) == hash::HashConst("baseclass")) { continue; }

		if (prop->recvType == SendPropType::DATATABLE
			&& prop->dataTable
			&& prop->dataTable->tableName[0] == 'D') {
			DumpNetvars(baseClass, prop->dataTable, offset + prop->offset);
		}
		const auto netvarName = std::format("{}->{}", baseClass, prop->varName);
		netvars[hash::Hash(netvarName.c_str())] = offset + prop->offset;
	}
}
