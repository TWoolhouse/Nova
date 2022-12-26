#pragma once
#include "meta/head.h"
#include "spec/buffer/self.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/buffer/buffer.h"
#endif // NOVA_ABYSS

namespace Nova::abyss::buffer {

	using Buffer =
	#if defined(NOVA_ABYSS_VULKAN)
	nvk::buffer::Buffer;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::buffer::Buffer<Buffer>, "Buffer invalidated the Spec");

} // namespace Nova::abyss
