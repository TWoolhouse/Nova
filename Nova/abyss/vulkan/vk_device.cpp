#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "device.h"

namespace Nova::abyss::vkn {

	Device::Device(Context& cxt) : cxt(cxt) {
		select_physical();
		create_logical();

		// Features is overwritten after the requested are used
		features = physical.getFeatures();

		// Moved to the swapchain
		// TODO: Remove
		swapchain = {
			physical.getSurfaceCapabilitiesKHR(cxt.surface),
			physical.getSurfaceFormatsKHR(cxt.surface),
			physical.getSurfacePresentModesKHR(cxt.surface)
		};

		for (auto& queue : queues) {
			logical.getQueue(queue.index, 0, &queue.queue);
		}

	}

	Device::~Device() {
		logical.destroy(cxt.alloc);
	}

	constexpr std::string_view get_device_type(const vk::PhysicalDeviceType type) {
		switch (type) {
		case vk::PhysicalDeviceType::eDiscreteGpu:	return "Discrete GPU";
		case vk::PhysicalDeviceType::eIntegratedGpu:	return "Integrated GPU";
		case vk::PhysicalDeviceType::eVirtualGpu:	return "Virtual GPU";
		case vk::PhysicalDeviceType::eCpu:	return "CPU";
		case vk::PhysicalDeviceType::eOther:
		default:
			return "Unknown";
		}
	}

	void Device::select_physical() {
		nvk_trace("Physical", "Selecting"sv, "Selected"sv);
		const auto devices = cxt.instance.enumeratePhysicalDevices();
		nova_assert(!devices.empty(), "No Vulkan Devices Found!");

		for (auto& device : devices) {
			nova_bark_debug("Device? {}", device.getProperties().deviceName);

			if (is_device_suitable(device)) {
				physical = device;
				break;
			}
		}
		nova_assert(physical, "No Physical Device matches the requirements");

		prop = physical.getProperties();
		memory = physical.getMemoryProperties();

		// Output Device Properties
		#if __N_OVA_BARK_STATE_INFO == 1
		{
			std::stringstream memory_info_local, memory_info_shared;
			for (auto it = memory.memoryHeaps.begin(), cend = memory.memoryHeaps.begin() + memory.memoryHeapCount; it != cend; ++it) {
				const auto& heap = *it;
				const auto size = heap.size / 1024.f / 1024.f / 1024.f;
				auto& stream = (heap.flags & vk::MemoryHeapFlagBits::eDeviceLocal) ? memory_info_local : memory_info_shared;
				stream << "\n\t\t" << size << " GiB ";
			}

			std::string memory_info_local_str = memory_info_local.str(), memory_info_shared_str = memory_info_shared.str();

			nova_bark_info("VK Device:\n\tName: {}\n\tType: {}\n\tAPI Version: {}.{}.{}\n\tDriver Version: {}.{}.{}\n\tLocal Memory:{}\n\tShared Memory:{}",
				prop.deviceName,
				get_device_type(prop.deviceType),
				VK_VERSION_MAJOR(prop.apiVersion),
				VK_VERSION_MINOR(prop.apiVersion),
				VK_VERSION_PATCH(prop.apiVersion),
				VK_VERSION_MAJOR(prop.driverVersion),
				VK_VERSION_MINOR(prop.driverVersion),
				VK_VERSION_PATCH(prop.driverVersion),
				memory_info_local_str.empty() ? " 0 B" : memory_info_local_str,
				memory_info_shared_str.empty() ? " 0 B" : memory_info_shared_str
			);
		}
		#endif // __N_OVA_BARK_STATE_INFO
	}

	void Device::create_logical() {
		nvk_tracec("Logical");

		auto indices = std::views::transform(queues, [](const auto& q) { return q.index; });
		const auto unique_queues = std::set<decltype(Q::index)>(indices.begin(), indices.end());

		std::vector<vk::DeviceQueueCreateInfo> queue_create_infos;
		for (const auto& index : unique_queues) {
			constexpr auto queues = std::array{ 1.0f };
			queue_create_infos.emplace_back(vk::DeviceQueueCreateFlags{}, index, queues);
		}

		features.samplerAnisotropy = true;

		std::vector<cstr> extensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		const auto create_info = vk::DeviceCreateInfo(vk::DeviceCreateFlags{}, queue_create_infos, {}, extensions, &features);
		logical = physical.createDevice(create_info, cxt.alloc);

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
#endif // NOVA_ABYSS_VULKAN
