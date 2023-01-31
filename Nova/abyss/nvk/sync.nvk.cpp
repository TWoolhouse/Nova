#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "sync.h"
#include "context.h"

namespace Nova::abyss::nvk {

	Semaphore::Semaphore() : self(nova_abyss_api->dev.createSemaphore({}, nova_abyss_api->alloc)) {}
	Semaphore::~Semaphore() { nova_abyss_api->dev.destroySemaphore(self, nova_abyss_api->alloc); }

	Fence::Fence() : self(nova_abyss_api->dev.createFence({}, nova_abyss_api->alloc)) {}
	Fence::Fence(bool signal) :
		self(nova_abyss_api->dev.createFence(vk::FenceCreateInfo{
			.flags = vk::FenceCreateFlagBits::eSignaled,
			}, nova_abyss_api->alloc)
		)
	{ NOVA_MC_UNUSED(signal); }
	Fence::~Fence() { nova_abyss_api->dev.destroyFence(self, nova_abyss_api->alloc); }

}

#endif // NOVA_ABYSS_VULKAN
