#include "../hooks.h"

enum hooks::ClientFrameStage : int32_t {
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};


void __stdcall hooks::FrameStageNotify(ClientFrameStage currentStage)
{
	if (currentStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
		hacks::skins::Change();
	}

	return oFrameStageNotify(currentStage);
}
