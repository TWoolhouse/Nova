#pragma once
#include "meta/head.h"
#include "spec/target_container.h"

#include "target_single.h"

namespace Nova::abyss {

	using Targets =
	#if defined(NOVA_ABYSS_VULKAN)
	std::vector<Target>;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::Targets<Targets>, "Targets invalidated the Spec");

} // namespace Nova::abyss
