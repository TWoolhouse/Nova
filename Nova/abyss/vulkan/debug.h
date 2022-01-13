#pragma once
#include "vk.h"
#include "context.h"

namespace Nova::abyss::vkn {

	vk::DebugUtilsMessengerCreateInfoEXT debug_info();
	void create_debugger(const Context& cxt);
	void destroy_debugger(const Context& cxt);

}