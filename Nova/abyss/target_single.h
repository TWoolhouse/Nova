#pragma once
#include "meta/head.h"
#include "spec/target.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/rendertarget.h"
#endif // NOVA_ABYSS

namespace Nova::abyss {

	using Target =
	#if defined(NOVA_ABYSS_VULKAN)
	nvk::RenderTarget;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::Target<Target>, "Target invalidated the Spec");

} // namespace Nova::abyss
