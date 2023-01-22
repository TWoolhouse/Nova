#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"
#include "context.h"

namespace Nova::abyss::nvk {

	Context::Context(const core::Information& info, const Setup& properties) :
		alloc(nullptr),
		instance(info, properties),
		device(properties),
		queues(device.info.queues),
		dev(device.logical),
		vma(),
		swapchain()
	{}

	Context::~Context() {
		dev.waitIdle();
	}

}

#endif // NOVA_ABYSS_VULKAN
