#include "../hooks.h"

void __stdcall hooks::DrawModel(
	void* result,
	CDrawModelInfo& info,
	CMatrix3x4* bones,
	float* flexWeights,
	float* flexDelayedWeights,
	Vector3& modelOrigin,
	int flags)
{
	if (globals::localPlayer && info.renderable)
	{
		CBaseEntity* entity = info.renderable->GetClientUnknown()->GetBaseEntity();

		if (entity && entity->IsPlayer()
			&& entity->GetTeam() != globals::localPlayer->GetTeam()
			&& !interfaces::render->IsForcedMaterialOverride())
		{
			static IMaterial* material = interfaces::materialSystem->FindMaterial("debug/debugambientcube");

			float hidden[3] = { 0.f, 1.f, 1.f };
			float visible[3] = { 1.f, 1.f, 0.f };

			interfaces::render->SetAlphaModulation(1.f);

			material->SetMaterialVarFlag(IMaterial::IGNOREZ, true);
			interfaces::render->SetColorModulation(hidden);
			interfaces::render->ForcedMaterialOverride(material);
			oDrawModel(interfaces::render, result, info, bones, flexWeights, flexDelayedWeights, modelOrigin, flags);

			material->SetMaterialVarFlag(IMaterial::IGNOREZ, false);
			interfaces::render->SetColorModulation(visible);
			interfaces::render->ForcedMaterialOverride(material);
			oDrawModel(interfaces::render, result, info, bones, flexWeights, flexDelayedWeights, modelOrigin, flags);

			return interfaces::render->ForcedMaterialOverride(nullptr);
		}
	}
	oDrawModel(interfaces::render, result, info, bones, flexWeights, flexDelayedWeights, modelOrigin, flags);
}