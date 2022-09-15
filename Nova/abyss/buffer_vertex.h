#pragma once
#include "meta/head.h"
#include "spec/buffer/vertex.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/buffer/vertex.h"
#endif // NOVA_ABYSS

namespace Nova::abyss::buffer {

	template<typename V>
	using Vertex =
	#if defined(NOVA_ABYSS_VULKAN)
	nvk::buffer::Vertex<V>;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::buffer::Vertex<Vertex>, "Vertex Buffer invalidated the Spec");

} // namespace Nova::abyss
