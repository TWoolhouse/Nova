#pragma once
#include "meta/head.h"
#include "spec/renderpass.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/renderpass.h"
#endif // NOVA_ABYSS

namespace Nova::abyss {

	using Renderpass =
	#if defined(NOVA_ABYSS_VULKAN)
	nvk::Renderpass;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::Renderpass<Renderpass>, "Renderpass invalidated the Spec");

} // namespace Nova::abyss
