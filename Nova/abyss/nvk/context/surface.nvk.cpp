#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"
#include "surface.h"
#include "context.h"

namespace Nova::abyss::nvk::Surface {

	void destroy(vk::SurfaceKHR& surface, vk::Instance& instance) {
		nova_bark_term("VK Surface");
		vkDestroySurfaceKHR(instance, surface, reinterpret_cast<std::remove_reference_t<decltype(*nova_abyss_api->alloc)>::NativeType*>(nova_abyss_api->alloc));
	}

}

#endif // NOVA_ABYSS_VULKAN
