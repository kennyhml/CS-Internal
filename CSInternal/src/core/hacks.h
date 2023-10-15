#include "globals.h"
#include "../csgo/cusercmd.h"
#include "../csgo/interfaces/isurface.h"
#include "../csgo/entity/cbaseattributableitem.h"

namespace hacks
{
	inline namespace esp
	{
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

		struct Rect { float x, y, w, h; };

		HFont GetTextFont(float targetDistance);
		HFont GetWeaponFont(float targetDistance);
		const wchar_t* GetWeaponIcon(int32_t weaponID);
		void DrawName(const char* name, Rect box, float distance);
		void DrawWeapon(int weaponID, Rect box, float distance);
		void DrawHealth(int health, Rect box);
		bool ShouldDrawEntity(CCSPlayer* entity);
		Rect GetBoundingRect(const Vector3& top, const Vector3& bottom);
		void Run(uintptr_t panel);
	}

	inline namespace skins
	{
		using Skin = uint32_t;

		Skin GetWeaponSkin(int32_t weaponID);
		bool SetSkin(CBaseAttributableItem* weapon, Skin skin);
		void ForceUpdateWeapon(CBaseAttributableItem* weapon);
		void Change();
	}

	void BunnyHop(CUserCmd* cmd);
	void TriggerBot(CUserCmd* cmd);
	void Aimbot(CUserCmd* cmd);
	void AntiFlash();
}