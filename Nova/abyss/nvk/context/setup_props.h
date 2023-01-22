#pragma once
#include "vk.h"

namespace Nova::abyss::nvk {

	struct Setup {
		std::vector<cstr> layers;
		std::vector<cstr> extensions_instance;
		std::vector<cstr> extensions_device;
		vk::PhysicalDeviceFeatures device_features;
	};

}
