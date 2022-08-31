#pragma once
#include "vk.h"

namespace Nova::abyss::nvk::Logger {

	vk::DebugUtilsMessengerEXT create(vk::Instance& instance);
	void destroy(vk::DebugUtilsMessengerEXT& logger, vk::Instance& instance);
	constexpr vk::DebugUtilsMessengerCreateInfoEXT info();

}
