// Pico4 interaction profile as per OpenXR 1.1.40 specification:
// https://registry.khronos.org/OpenXR/specs/1.1/html/xrspec.html#_bytedance_pico_4_controller_profile
//
// Template: Oculus interaction profile by ZNix
//

#include "stdafx.h"

#include "Pico4InteractionProfile.h"

Pico4InteractionProfile::Pico4InteractionProfile()
{

	const char* paths[] = {
		"/user/hand/left/input/x/click",
		"/user/hand/left/input/x/touch",
		"/user/hand/left/input/y/click",
		"/user/hand/left/input/y/touch",
		"/user/hand/left/input/menu/click",
		"/user/hand/right/input/a/click",
		"/user/hand/right/input/a/touch",
		"/user/hand/right/input/b/click",
		"/user/hand/right/input/b/touch",
		// Runtimes are not required to support the system button paths, and no OpenVR game can use it anyway.
		//"/user/hand/right/input/system/click",
	};

	const char* perHandPaths[] = {
		"/input/trigger/click",
		"/input/trigger/value",
		"/input/trigger/touch"
		"/input/thumbstick/y",
		"/input/thumbstick/x",
		"/input/thumbstick/click",
		"/input/thumbstick/touch",
		"/input/squeeze/click",
		"/input/squeeze/value",
		"/input/grip/pose",
		"/input/aim/pose",
		"/output/haptic",
		//"/input/grip_surface/pose", // Hand tracking related?
		//"/input/palm_ext/pose", // Hand tracking related?
		//"/input/pinch_ext/pose", // Hand tracking related?
		//"/input/poke_ext/pose", // Hand tracking related?

	};

	for (const char* str : paths) {
		this->validInputPaths.insert(str);
	}

	for (const char* str : perHandPaths) {
		this->validInputPaths.insert("/user/hand/left" + std::string(str));
		this->validInputPaths.insert("/user/hand/right" + std::string(str));
	}

	this->pathTranslationMap = {
		{ "grip", "squeeze" },
		{ "joystick", "thumbstick" },
		{ "pull", "value" },
		{ "grip/click", "squeeze/value" },
		{ "trigger/click", "trigger/value" },
		{ "application_menu", "menu" }
	};
	// TODO implement the poses through the interaction profile (the raw pose is hard-coded in BaseInput at the moment):
	// pose/raw
	// pose/base
	// pose/handgrip
	// pose/tip

	this->hmdPropertiesMap = {
		{ vr::Prop_TrackingSystemName_String, "Pico4" },
		{ vr::Prop_ManufacturerName_String, "Bytedance" },
	};

	this->propertiesMap = {
		{ vr::Prop_TrackingSystemName_String, { "Pico4" } },
		{ vr::Prop_ModelNumber_String, { "Left Controller", "Right Controller" } },
		{ vr::Prop_ControllerType_String, { GetOpenVRName().value() } }
	};

}

const std::string& Pico4InteractionProfile::GetPath() const
{
	static std::string path = "/interaction_profiles/bytedance/pico4_controller";
	return path;
}

std::optional<const char*> Pico4InteractionProfile::GetLeftHandRenderModelName() const
{
	return std::nullopt; // Has model?
}

std::optional<const char*> Pico4InteractionProfile::GetRightHandRenderModelName() const
{
	return std::nullopt; // Has model?
}

std::optional<const char*> Pico4InteractionProfile::GetOpenVRName() const
{
	return "monado_bytedance_pico4_controller"; // From steamvr-monado/resources/input/bytedance_pico4_controller_profile.json
}

const InteractionProfile::LegacyBindings* Pico4InteractionProfile::GetLegacyBindings(const std::string& handPath) const
{
	static LegacyBindings allBindings[2] = { {}, {} };
	int hand = handPath == "/user/hand/left" ? vr::Eye_Left : vr::Eye_Right;
	LegacyBindings& bindings = allBindings[hand];

	// First-time initialisation
	if (!bindings.menu) {
		bindings = {};

		if (handPath == "/user/hand/left") {
			bindings.btnA = "/input/x/click";
			bindings.btnATouch = "/input/x/touch";
			bindings.menu = "/input/y/click";
			bindings.menuTouch = "/input/y/touch";
			bindings.system = "/input/menu/click";
		} else {
		bindings.btnA = "/input/a/click";
		bindings.btnATouch = "/input/a/touch";
		bindings.menu = "/input/b/click";
		bindings.menuTouch = "/input/b/touch";
		}

		bindings.triggerClick = "/input/trigger/click";
		bindings.trigger = "/input/trigger/value";
		bindings.triggerTouch = "/input/trigger/touch";
		bindings.stickY = "/input/thumbstick/y";
		bindings.stickX = "/input/thumbstick/x";
		bindings.stickBtn = "/input/thumbstick/click";
		bindings.stickBtnTouch = "/input/thumbstick/touch";
		//bindings.gripClick = "/input/squeeze/click"; // INOP
		bindings.grip = "/input/squeeze/value";
		bindings.gripPoseAction = "/input/grip/pose";
		bindings.aimPoseAction = "/input/aim/pose";
		bindings.haptic = "/output/haptic";

	}
	return &bindings;
}
