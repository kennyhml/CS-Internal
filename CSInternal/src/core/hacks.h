#include "../csgo/cusercmd.h"
#include "globals.h"
#include "../csgo/interfaces/isurface.h"

namespace fonts
{
	inline HFont textTiny;
	inline HFont textMedium;
	inline HFont textBig;

	inline HFont weaponTiny;
	inline HFont weaponMedium;
	inline HFont weaponBig;

	void Init();
}



namespace hacks
{
	void BunnyHop(CUserCmd* cmd);
	void TriggerBot(CUserCmd* cmd);
	void Aimbot(CUserCmd* cmd);
	void Esp(uintptr_t panel);
}