#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"
#include "device_logical.h"
#include "context.h"

namespace Nova::abyss::nvk::Logical {

	void log_queues(Queues& queues) {
		if constexpr (Nova::bark::def::info) {
			for (const auto& q : queues.all()) {
				auto count = std::ranges::count(queues.all(), q.self, &std::remove_cvref_t<decltype(q)>::self);
				nova_bark_info("\t{:<8} | Family {} | {} Q", q.type, q.family, count > 1 ? nova_bark_format("Shared[{}]", count) : "Unique");
			}
		}
	}
	void log_device() {

	}

	// TODO: Migrate to VkPhysicalDeviceFeatures2
	vk::Device create(const prop::Setup& properties, vk::PhysicalDevice& physical, Queues& queues) {
		nova_bark_init("VK Logical Device");

		std::array<Q::FQCount, Queues::count> qf_queue_count{0};
		for (auto& q : queues.all()) {
			if (static_cast<bool>(q.type & Q::Type::Merge)) continue;
			++qf_queue_count[q.family];
		}

		std::array<float, Queues::count> queue_prioritiy;
		std::fill(queue_prioritiy.begin(), queue_prioritiy.end(), 1.0f);
		std::vector<vk::DeviceQueueCreateInfo> info_queue;
		for (Q::Index family = 0; family < qf_queue_count.size(); ++family) {
			const auto& qf_count = qf_queue_count[family];
			if (qf_count)
				info_queue.push_back(
					vk::DeviceQueueCreateInfo {
						.queueFamilyIndex = family,
						.queueCount = qf_count,
						// TODO: Queue priorities
						.pQueuePriorities = queue_prioritiy.data(),
					}
				);
		}

		vk::DeviceCreateInfo info_device{
			.queueCreateInfoCount = static_cast<uint32_t>(info_queue.size()),
			.pQueueCreateInfos = info_queue.data(),
			.enabledExtensionCount = static_cast<uint32_t>(properties.extensions_device.size()),
			.ppEnabledExtensionNames = properties.extensions_device.data(),
			.pEnabledFeatures = &properties.device_features,
		};

		auto device = NVK_CHECK(physical.createDevice(info_device, nova_abyss_api->alloc), "Failed to create Device");

		nova_bark_init("VK Queues");
		for (auto& q : std::views::reverse(queues.all())) {
			q.self = device.getQueue(q.family, --qf_queue_count[q.family]);
			if (static_cast<bool>(q.type & Q::Type::Merge)) {
				++qf_queue_count[q.family];
				q.type &= ~Q::Type::Merge;
			}
		}

		log_queues(queues);
		log_device();

		return device;
	}

}

#endif // NOVA_ABYSS_VULKAN
