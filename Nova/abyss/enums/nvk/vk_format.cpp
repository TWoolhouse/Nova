#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"

nova_meta_enum_str(vk::Format, format) {
	switch (format) {
		case vk::Format::eB8G8R8A8Srgb: return "B8-G8-R8-A8-Srgb";
		default:
			nova_bark_warn("Unknown Case [vk Format]: {}", static_cast<std::underlying_type_t<decltype(format)>>(format));
			return "Unknown";
	}
}

#endif // NOVA_ABYSS_VULKAN
