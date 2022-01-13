#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "context.h"
#include "instance.h"
#include "surface.h"

namespace Nova::abyss::vkn {

	Context::Context(const std::string_view& name) : alloc(nullptr) {
		nova_bark_init("[Abyss] <Vulkan> ...");
		create_instance(*this, name);
		create_surface(*this);
		nova_bark_init("[Abyss] Done!");
	}

	Context::~Context() {
		nova_bark_term("[Abyss] ...");
		vkDestroySurfaceKHR(instance, surface, *this);
		destroy_instance(*this);
		nova_bark_term("[Abyss] Done!");
	}

}
#endif // NOVA_ABYSS_VULKAN