#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"
#include "device.h"
#include "device_physical.h"
#include "device_logical.h"
#include "context.h"

namespace Nova::abyss::nvk {

	Device::Device(const Setup& properties) :
		info(),
		physical(PhysicalBuilder(properties).select_device(info)),
		logical(Logical::create(properties, physical, info.queues))
	{

	}
	Device::~Device() {
		nova_bark_term("VK Logical Device");
		logical.destroy(nova_abyss_api->alloc);
	}

}

#endif	// NOVA_ABYSS_VULKAN
