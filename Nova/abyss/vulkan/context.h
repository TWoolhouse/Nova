#pragma once
#include "vk.h"

namespace Nova::abyss::vkn {

	struct Context {
		vk::AllocationCallbacks* alloc;
		vk::Instance instance;
		vk::SurfaceKHR surface;

		Context(const std::string_view& name);
		~Context();
	private:
		void create_instance(const std::string_view& name);
		void create_surface();
		void destroy_instance();
	};

}