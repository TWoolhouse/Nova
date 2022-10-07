#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "buffer.h"
#include "../context.h"

namespace Nova::abyss::nvk::buffer {

	Raw::~Raw() {
		nova_bark_term("Buffer");
		vmaDestroyBuffer(nova_abyss_api->vma, buffer, allocation);
	}

	Raw::Raw(size_t size) {
		nova_bark_init("VK Buffer");
		vk::BufferCreateInfo info_buffer{
			.size = size,
			.usage = vk::BufferUsageFlagBits::eVertexBuffer,
		};

		VmaAllocationCreateInfo info_allocation{
			.flags = {},
			.usage = VMA_MEMORY_USAGE_AUTO,
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
				reinterpret_cast<VkBuffer*>(&buffer),
				&allocation,
				info_ptr
			), "Failed to create VMA Buffer"
		);

		if constexpr (debug) {
			nova_bark_debug("VK Buffer Allocation: {}B {} {}",
				info.size,
				info.pMappedData ? "Mapped" : "Unmapped",
				static_cast<std::underlying_type_t<vk::BufferUsageFlagBits>>(info_buffer.usage)
			);
		}

	}

}

#endif // NOVA_ABYSS_VULKAN
