#include "npch.h"
#define VMA_IMPLEMENTATION
#include "vma.h"
#include "context.h"

namespace Nova::abyss::nvk {

	VMA::VMA() : self(VMA_NULL) {
		nova_bark_init("VK VMA");
		VmaAllocatorCreateInfo info_allocator{
			.flags = {},
			.physicalDevice = nova_abyss_api->device.physical,
			.device = nova_abyss_api->dev,
			.pAllocationCallbacks = reinterpret_cast<VkAllocationCallbacks*>(nova_abyss_api->alloc),
			.instance = nova_abyss_api->instance,
			.vulkanApiVersion = VK_VERSION,
		};
		NVK_RESULT(vmaCreateAllocator(&info_allocator, &self), "Failed to create VMA Allocator");
	}

	VMA::~VMA() {
		nova_bark_term("VK VMA");
		vmaDestroyAllocator(self);
	}

}