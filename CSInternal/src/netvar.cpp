#include "netvar.h"
#include "interfaces.h"
#include <ctype.h>
#include <format>

void SetupNetvars()
{
	for (auto clientClass = client->GetAllClasses(); clientClass; clientClass = clientClass->next)
	{
		if (clientClass->recvTable) {
			Dump(clientClass->networkName, clientClass->recvTable);
		}
	}
}

void Dump(const char* baseClass, RecvTable* table, std::uint32_t offset)
{
	for (int i = 0; i < table->propsCount; i++)
	{
		const auto prop = &table->props[i];
		if (!prop || isdigit(prop->varName[0])) { continue; }

		if (fnv::Hash(prop->varName) == fnv::HashConst("baseclass")) { continue; }

		if (prop->recvType == SendPropType::DATATABLE
			&& prop->dataTable
			&& prop->dataTable->tableName[0] == 'D') {
			Dump(baseClass, prop->dataTable, offset + prop->offset);
		}
		const auto netvarName = std::format("{}->{}", baseClass, prop->varName);
		std::cout << baseClass << "->" << prop->varName << ": " << std::hex << offset + prop->offset << "\n";
		netvars[fnv::Hash(netvarName.c_str())] = offset + prop->offset;
	}
}
