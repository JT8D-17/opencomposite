// Pico4 interaction profile as per OpenXR 1.1.40 specification:
// https://registry.khronos.org/OpenXR/specs/1.1/html/xrspec.html#_bytedance_pico_4_controller_profile
//
// Template: Oculus interaction profile by ZNix
//

#pragma once

#include "InteractionProfile.h"

class Pico4InteractionProfile : public InteractionProfile {
public:
	Pico4InteractionProfile();

	const std::string& GetPath() const override;
	std::optional<const char*> GetLeftHandRenderModelName() const override;
	std::optional<const char*> GetRightHandRenderModelName() const override;
	std::optional<const char*> GetOpenVRName() const override;

protected:
	const LegacyBindings* GetLegacyBindings(const std::string& handPath) const override;
};
