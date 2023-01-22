#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "pool.h"
#include "../context.h"

namespace Nova::abyss::nvk::descriptor {

	Pool::Pool() {
		nova_bark_init("VK Descriptor Pool");
		constexpr std::array<vk::DescriptorPoolSize, 1> sizes{
			{ vk::DescriptorType::eUniformBuffer, 10 },
		};

		vk::DescriptorPoolCreateInfo info{
			.flags = {},
			.maxSets = 10, // TODO: The sum of all the sizes
			.poolSizeCount = sizes.size(),
			.pPoolSizes = sizes.data(),
		};

		self = NVK_CHECK(nova_abyss_api->dev.createDescriptorPool(info, nova_abyss_api->alloc), "Failed to create Descriptor Pool");
	}

	Pool::~Pool() {
		nova_bark_term("VK Descriptor Pool");
		nova_abyss_api->dev.destroyDescriptorPool(self, nova_abyss_api->alloc);
	}

}

#endif // NOVA_ABYSS_VULKAN