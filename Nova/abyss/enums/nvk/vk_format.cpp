#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"

nova_meta_enum_str(vk::Format, format) {
	switch (format) {
		case vk::Format::eB8G8R8A8Srgb: return "B8-G8-R8-A8-Srgb";
		case vk::Format::eR32Sfloat: return "float";
		case vk::Format::eR32G32Sfloat: return "vec2<float>";
		case vk::Format::eR32G32B32Sfloat: return "vec3<float>";
		case vk::Format::eR32G32B32A32Sfloat: return "vec4<float>";
		case vk::Format::eR64Sfloat: return "double";
		case vk::Format::eR64G64Sfloat: return "vec2<double>";
		case vk::Format::eR64G64B64Sfloat: return "vec3<double>";
		case vk::Format::eR64G64B64A64Sfloat: return "vec4<double>";
		case vk::Format::eR32Sint: return "int";
		case vk::Format::eR32G32Sint: return "vec2<int>";
		case vk::Format::eR32G32B32Sint: return "vec3<int>";
		case vk::Format::eR32G32B32A32Sint: return "vec4<int>";
		case vk::Format::eR32Uint: return "uint";
		case vk::Format::eR32G32Uint: return "vec2<uint>";
		case vk::Format::eR32G32B32Uint: return "vec3<uint>";
		case vk::Format::eR32G32B32A32Uint: return "vec4<uint>";
		default:
			nova_bark_warn("Unknown Case [vk Format]: {}", cpp::to_underlying(format));
			return "Unknown";
	}
}

#endif // NOVA_ABYSS_VULKAN
