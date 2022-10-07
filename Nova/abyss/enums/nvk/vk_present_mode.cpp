#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"

nova_meta_enum_str(vk::PresentModeKHR, mode) {
	switch (mode) {
		case vk::PresentModeKHR::eImmediate: return "Immediate";
		case vk::PresentModeKHR::eMailbox: return "Mailbox";
		case vk::PresentModeKHR::eFifo: return "Fifo";
		case vk::PresentModeKHR::eFifoRelaxed: return "Fifo Relaxed";
		case vk::PresentModeKHR::eSharedDemandRefresh: return "Shared Demand Refresh";
		case vk::PresentModeKHR::eSharedContinuousRefresh: return "Shared Continuous Refresh";
		default:
			nova_bark_warn("Unknown Case [vk Present Mode]: {}", cpp::to_underlying(mode));
			return "Unknown";
	}
}

#endif // NOVA_ABYSS_VULKAN
