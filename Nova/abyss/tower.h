#pragma once
#include "meta/head.h"
#include "spec/tower.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/tower.h"
#endif // NOVA_ABYSS

namespace Nova::abyss {

	using Tower =
	#if defined(NOVA_ABYSS_VULKAN)
	nvk::Tower;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::Tower<Tower>, "Tower invalidated the Spec");

} // namespace Nova::abyss
