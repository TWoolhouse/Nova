#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "context.h"
#include "instance.h"
#include "surface.h"

namespace Nova::abyss::vkn {

	Context::Context(const std::string_view& name) : alloc(nullptr) {
		create_instance(*this, name);
		create_surface(*this);
	}

	Context::~Context() {
		vkDestroySurfaceKHR(instance, surface, *this);
		destroy_instance(*this);
	}

}
#endif // NOVA_ABYSS_VULKAN
