#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "abyss/nvk/context/queues.h"

nova_meta_enum_str(Nova::abyss::nvk::Q::Type, type) {
	using Type = std::remove_cvref_t<decltype(type)>;
	switch (type) {
		case Type::Graphics: return "Graphics";
		case Type::Compute: return "Compute";
		case Type::Transfer: return "Transfer";
		case Type::Present: return "Present";
		default:
			nova_bark_warn("Unknown Case [Queue Type]: {}", cpp::to_underlying(type));
			return "Unknown";
	}
}

#endif // NOVA_ABYSS_VULKAN
