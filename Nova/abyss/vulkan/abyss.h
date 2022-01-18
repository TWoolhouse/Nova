#pragma once
#include "../abyss.h"
#include "context.h"
#include "device.h"
#include "swapchain.h"

namespace Nova::abyss::vkn {

	struct Abyss {
		vkn::Context cxt;
		vkn::Device device;
		vkn::Swapchain swapchain;
		Abyss(const std::string_view& name);
	};

}