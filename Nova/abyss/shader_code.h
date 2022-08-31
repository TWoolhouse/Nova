#pragma once
#include "meta/head.h"
#include "spec/shader_code.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/shader/code.h"
#endif // NOVA_ABYSS

namespace Nova::abyss {

	using ShaderCode =
	#if defined(NOVA_ABYSS_VULKAN)
	nvk::ShaderCode;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::ShaderCode<ShaderCode>, "Shader invalidated the Spec");

} // namespace Nova::abyss
