#include "../csgo/cusercmd.h"
#include "globals.h"
#include "../csgo/interfaces/isurface.h"

namespace fonts
{
	inline HFont tiny;
	inline HFont medium;
	inline HFont big;

	void Init();

}



namespace hacks
{
	void BunnyHop(CUserCmd* cmd);
	void TriggerBot(CUserCmd* cmd);
	void Aimbot(CUserCmd* cmd);
	void Esp(uintptr_t panel);
}