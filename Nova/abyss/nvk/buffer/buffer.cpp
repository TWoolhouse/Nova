#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "buffer.h"
#include "../context.h"

namespace Nova::abyss::nvk::buffer {

	Raw::~Raw() {
		nova_bark_term("Buffer");
		vmaDestroyBuffer(nova_abyss_api->vma, self, allocation);
	}

	Raw::Raw(size_t size, Type type) {
		nova_bark_init("VK Buffer");
		vk::BufferCreateInfo info_buffer{
			.size = size,
			.usage = static_cast<vk::BufferUsageFlagBits>(type),
		};
		VmaAllocationCreateInfo info_allocation{
			.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT,
			.usage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST,
		};

		VmaAllocationInfo info;

		auto info_ptr = &info;
		constexpr auto debug = abyss::def::debug && bark::def::debug;
		if constexpr (!debug)
			info_ptr = nullptr;

		NVK_RESULT(
			vmaCreateBuffer(
				nova_abyss_api->vma,
				reinterpret_cast<VkBufferCreateInfo*>(&info_buffer),
				&info_allocation,
				reinterpret_cast<VkBuffer*>(&self),
				&allocation,
				info_ptr
			), "Failed to create VMA Buffer"
		);

		if constexpr (debug) {
			nova_bark_debug("VK Buffer Allocation: {}B {} {}",
				info.size,
				info.pMappedData ? "Mapped" : "Unmapped",
				type
			);
		}

	}

	void* Raw::mapping() {
		VmaAllocationInfo info;
		vmaGetAllocationInfo(nova_abyss_api->vma, allocation, &info);
		return info.pMappedData;
	}

}

#endif // NOVA_ABYSS_VULKAN
