#pragma once
#include "vk.h"
#include "props.h"
#include "queues.h"
#include "device.h"

namespace Nova::abyss::nvk {

	// Helper to obtain the physical device
	struct PhysicalBuilder {
	public:
		PhysicalBuilder(const prop::Setup& properties) : properties(properties) {}

		vk::PhysicalDevice select_device(Device::Info& info);
	protected:
		const prop::Setup& properties;

		struct Rank {
			using Score = size_t;
			vk::PhysicalDevice device;
			Score score = 0;
			Device::Info info;
		};
		std::vector<Rank> device_ranks;
		inline Device::Info& current_device_info() { return device_ranks.back().info; }

		void rank_devices(std::vector<vk::PhysicalDevice>& devices);
		Rank::Score score_device_suitablility(vk::PhysicalDevice& device);

		Rank::Score test_features(vk::PhysicalDevice& device);
		Rank::Score test_extensions(vk::PhysicalDevice& device);
		Rank::Score queue_families(vk::PhysicalDevice& device);
		Rank::Score rank_type(vk::PhysicalDevice& device);

		Rank::Score swapchain_surface_format(vk::PhysicalDevice& device);
		Rank::Score swapchain_present_mode(vk::PhysicalDevice& device);		

		std::vector<Q::Index> assign_queues(vk::PhysicalDevice& device, Q::Type type, std::vector<vk::QueueFamilyProperties>& families);

	};

}
