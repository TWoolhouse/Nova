#pragma once
#include "meta/head.h"
#include "spec/buffer/scope.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/buffer/scope.h"
#endif // NOVA_ABYSS

namespace Nova::abyss::buffer {

	using Scope =
	#if defined(NOVA_ABYSS_VULKAN)
	nvk::buffer::Scope;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::buffer::Scope<Scope>, "Scope Enum invalidated the Spec");

} // namespace Nova::abyss

nova_meta_enum_str(Nova::abyss::buffer::Scope, scope);
