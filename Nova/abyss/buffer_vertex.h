#pragma once
#include "meta/head.h"
#include "spec/null.h"

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

	using VertexI =
	#if defined(NOVA_ABYSS_VULKAN)
	nvk::buffer::VertexGeneric;
	#else
	spec::null;
	#endif // NOVA_ABYSS


} // namespace Nova::abyss

// The specs require the above to be defined already
#include "spec/buffer/vertex.h"

namespace Nova::abyss::buffer {

	static_assert(spec::buffer::Vertex<Vertex>, "Vertex Buffer invalidated the Spec");
	 static_assert(spec::buffer::VertexI<VertexI>, "Generic Vertex Buffer invalidated the Spec");

} // namespace Nova::abyss
