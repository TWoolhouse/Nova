#pragma once
#include "meta/head.h"
#include "spec/shader.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/shader.h"
#endif // NOVA_ABYSS

namespace Nova::abyss {

	using Shader =
	#if defined(NOVA_ABYSS_VULKAN)
	nvk::Shader;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::Shader<Shader>, "Shader invalidated the Spec");

	namespace shader {
		using Stage = abyss::Shader::Stage;
	} // namespace shader

} // namespace Nova::abyss

nova_meta_enum_str(Nova::abyss::Shader::Stage, stage);
