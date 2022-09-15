#pragma once
#include "meta/head.h"
#include "spec/shader_graphics.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/shader/graphics.h"
#endif // NOVA_ABYSS

namespace Nova::abyss::shader {

	using Graphics =
	#if defined(NOVA_ABYSS_VULKAN)
	nvk::shader::Graphics;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::shader::Graphics<Graphics>, "Shader invalidated the Spec");

} // namespace Nova::abyss
