#include "npch.h"
#include "device.h"

namespace Nova::abyss {

	Device::Device(Context& cxt) : cxt(cxt) {
		select_physical();
		create_logical();
	}

	Device::~Device() {}

	void Device::select_physical() {
		nvk_tracec(Selecting, "Physical");
		const auto devices = cxt.instance.enumeratePhysicalDevices();
		nova_assert(!devices.empty(), "No Vulkan Devices Found!");

		for (auto& device : devices) {
			nova_bark_debug("Device? {}", device.getProperties().deviceName);

			if (is_device_suitable(device)) {
				physical = device;
				physical_properties = physical.getProperties();
				break;
			}
		}
		nova_assert(physical, "No Physical Device matches the requirements");
		nova_bark_info("VK Device: {}", physical_properties.deviceName);
	}

	void Device::create_logical() {
		nvk_tracec(Creating, "Logical");

	}

	bool Device::is_device_suitable(const vk::PhysicalDevice& device) {
		const auto queue_families = device.getQueueFamilyProperties();

		// Graphics | Compute | Transfer Queue Index
		for (auto& que : std::views::filter(queues, [](const auto& q) { return static_cast<unsigned int>(q.type); })) {
			if (auto result = std::ranges::find_if(queue_families,
				[&que](const auto& qfp) { return static_cast<bool>(qfp.queueFlags & que.type); }
			); result != queue_families.cend()) {
				que.index = std::distance(queue_families.cbegin(), result);
				que.count = result->queueCount;
			}
		}

		// Present Queue Index
		for (uint32_t i = 0, end = queue_families.size(); i < end; ++i) {
			if (device.getSurfaceSupportKHR(i, cxt.surface)) {
				queue.present.index = i;
			}
		}

		// Make sure nothing is left as Invalid
		for (const auto& que : queues) {
			if (que.index == Queues::Invalid) {
				return false;
			}
		}
		return true;
	}

}