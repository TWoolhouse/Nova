#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"

nova_meta_enum_str(vk::PhysicalDeviceType, type) {
	using Type = std::remove_cvref_t<decltype(type)>;
	switch (type) {
		case Type::eDiscreteGpu: return "Discrete GPU";
		case Type::eIntegratedGpu: return "Integrated GPU";
		case Type::eVirtualGpu: return "Virtual GPU";
		case Type::eCpu: return "CPU";
		case Type::eOther: [[fallthrough]];
		default:
			nova_bark_warn("Unknown Case [vk Physical Device Type]: {}", static_cast<std::underlying_type_t<decltype(type)>>(type));
			return "Unknown";
	}
}

#endif // NOVA_ABYSS_VULKAN
