#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "surface.h"

namespace Nova::abyss::vkn {

	void create_surface(Context& cxt) {
		nvk_tracec(Creating, "Surface");
		create_surface_platform(cxt);
		nova_assert(cxt.surface, "Failed to Create VK Instance");
		nvk_tracef(Created, "Surface");
	}

	// void create_surface_platform(Context& cxt);
	// Implemented in platform_*.cpp

}
#endif // NOVA_ABYSS_VULKAN
