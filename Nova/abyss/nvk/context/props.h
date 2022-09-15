#pragma once
#include "vk.h"

namespace Nova::abyss::nvk::prop {

	struct Setup {
		std::string_view app_name;
		std::vector<cstr> layers;
		std::vector<cstr> extensions_instance;
		std::vector<cstr> extensions_device;
		vk::PhysicalDeviceFeatures device_features;
	};

}
