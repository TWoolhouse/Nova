#pragma once
#include "vk.h"

namespace Nova::abyss::nvk::Logger {

	NODISCARD vk::DebugUtilsMessengerEXT create(vk::Instance& instance);
	void destroy(vk::DebugUtilsMessengerEXT& logger, vk::Instance& instance);
	NODISCARD constexpr vk::DebugUtilsMessengerCreateInfoEXT info();

}
