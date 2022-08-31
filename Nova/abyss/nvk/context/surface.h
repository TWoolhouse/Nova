#pragma once
#include "vk.h"

namespace Nova::abyss::nvk::Surface {

	vk::SurfaceKHR create(vk::Instance& instance);
	void destroy(vk::SurfaceKHR& surface, vk::Instance& instance);
}
