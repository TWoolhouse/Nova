#pragma once
#include "meta/head.h"
#include "spec/buffer/type.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/buffer/type.h"
#endif // NOVA_ABYSS

namespace Nova::abyss::buffer {

	using Type =
	#if defined(NOVA_ABYSS_VULKAN)
	nvk::buffer::Type;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::buffer::Type<Type>, "Type Enum invalidated the Spec");

} // namespace Nova::abyss

nova_meta_enum_str(Nova::abyss::buffer::Type, type);
