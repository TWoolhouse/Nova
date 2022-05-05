#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "context.h"

namespace Nova::abyss::vkn {

	Context::Context(const std::string_view& name) : alloc(), instance(), surface() {
		nvk_tracec("Context");
		create_instance(name);
		{
			nvk_tracec("Surface");
			create_surface();
		}
	}

	Context::~Context() {
		nvk_traced("Context");
		{
			nvk_traced("Surface");
			vkDestroySurfaceKHR(instance, surface, reinterpret_cast<std::remove_reference_t<decltype(*alloc)>::NativeType*>(alloc));
		}
		destroy_instance();
	}

}

#endif // NOVA_ABYSS_VULKAN
