#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"

nova_meta_enum_str(vk::MemoryPropertyFlagBits, flag) {
	using Type = decltype(flag);
	switch (flag) {
	case Type::eDeviceLocal: return "Device Local";
	case Type::eHostVisible: return "Host Visable";
	case Type::eHostCoherent: return "Host Coherent";
	default:
		nova_bark_warn("Unknown Case [vk Memory Property]: {}", cpp::to_underlying(flag));
		return "Unknown";
	}
}

#endif // NOVA_ABYSS_VULKAN
