#include <memory>

struct CPlayerInfo
{
	uint64_t version;
	union
	{
		uint64_t xuid;
		struct
		{
			uint32_t xuidLow;
			uint32_t xuidHigh;
		};
	};
	char name[128];
	int userId;
	char guid[33];
	uint32_t friendsId;
	char friendsName[128];
	bool fakeplayer;
	bool hltv;
	int customfiles[4];
	unsigned char filesdownloaded;
	int entityIndex;
};