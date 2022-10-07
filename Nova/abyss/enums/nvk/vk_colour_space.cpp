#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"

nova_meta_enum_str(vk::ColorSpaceKHR, format) {
	switch (format) {
		case vk::ColorSpaceKHR::eSrgbNonlinear: return "Srgb-Nonlinear";
		default:
			nova_bark_warn("Unknown Case [vk Colour Space]: {}", cpp::to_underlying(format));
			return "Unknown";
	}
}

#endif // NOVA_ABYSS_VULKAN
