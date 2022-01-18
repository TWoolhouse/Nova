#pragma once
#include "vk.h"

namespace Nova::abyss::vkn {

	struct Context {
		Context(const std::string_view& name);
		Context(const Context&) = delete;
		Context& operator=(const Context&) = delete;
		~Context();
		vk::Instance instance;
		vk::SurfaceKHR surface;
		const vk::AllocationCallbacks* alloc;

		NODISCARD operator decltype(instance)&() { return instance; }
		NODISCARD operator decltype(instance)::CType() const { return instance; }
		NODISCARD operator auto() const { return reinterpret_cast<const std::remove_pointer_t<decltype(alloc)>::NativeType*>(alloc); }

	};

}
