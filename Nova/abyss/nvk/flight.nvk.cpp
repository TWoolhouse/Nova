#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "flight.h"
#include "context.h"

namespace Nova::abyss::nvk {

	Flight::Flight() :
		abyss::Flight{
			.commands = VK_NULL_HANDLE,
		},
		sync(),
		cmd(),
		swapchain_frame_index(std::numeric_limits<decltype(swapchain_frame_index)>::max())
	{
		commands = nova_abyss_api->dev.allocateCommandBuffers(vk::CommandBufferAllocateInfo{
			.commandPool = cmd.pool,
			.level = vk::CommandBufferLevel::eSecondary,
			.commandBufferCount = 1,
		})[0];
	}

	Flight::Command::Command() :
		pool(nova_abyss_api->dev.createCommandPool(vk::CommandPoolCreateInfo{
			.flags = {},
			.queueFamilyIndex = nova_abyss_api->queues.graphics.family
		}, nova_abyss_api->alloc)),
		buffer(nova_abyss_api->dev.allocateCommandBuffers(vk::CommandBufferAllocateInfo{
			.commandPool = pool,
			.level = vk::CommandBufferLevel::ePrimary,
			.commandBufferCount = 1,
		})[0])
	{}

	Flight::Command::~Command() {
		nova_abyss_api->dev.destroyCommandPool(pool, nova_abyss_api->alloc);
	}

}

#endif // NOVA_ABYSS_VULKAN
