#pragma once
#include "../abyss.h"
#include "context.h"
#include "device.h"

namespace Nova::abyss::vkn {

	struct Abyss {
		vkn::Context cxt;
		vkn::Device device;
		Abyss(const std::string_view& name);
	};

}