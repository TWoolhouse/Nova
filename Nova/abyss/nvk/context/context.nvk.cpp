#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"
#include "context.h"

namespace Nova::abyss::nvk {

	Context::Context(const prop::Setup& properties) :
		// Use the first param to initialise the context pointer before everything else
		alloc(nullptr),
		instance(properties),
		device(properties),
		queues(device.info.queues),
		dev(device.logical),
		swapchain()
	{

	}

	Context::~Context() {
		dev.waitIdle();
	}

}

#endif // NOVA_ABYSS_VULKAN
