#pragma once
#include "meta/head.h"
#include "spec/buffer/format.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/buffer/format.h"
#endif // NOVA_ABYSS

namespace Nova::abyss::buffer {

	using Format =
	#if defined(NOVA_ABYSS_VULKAN)
	nvk::buffer::Format;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::buffer::Format<Format>, "Format invalidated the Spec");

} // namespace Nova::abyss
