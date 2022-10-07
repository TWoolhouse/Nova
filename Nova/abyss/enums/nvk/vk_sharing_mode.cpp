#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"

nova_meta_enum_str(vk::SharingMode, mode) {
	switch (mode) {
		case vk::SharingMode::eExclusive: return "Exclusive";
		case vk::SharingMode::eConcurrent: return "Concurrent";
		default:
			nova_bark_warn("Unknown Case [vk Sharing Mode]: {}", cpp::to_underlying(mode));
			return "Unknown";
	}
}

#endif // NOVA_ABYSS_VULKAN
