#pragma once
#include "vk.h"
#include "context.h"

namespace Nova::abyss::vkn {

	class Device {
	protected:
		Context& cxt;
	public:
		vk::PhysicalDevice physical;
		vk::Device logical;

		vk::PhysicalDeviceProperties prop;
		vk::PhysicalDeviceFeatures features;
		vk::PhysicalDeviceMemoryProperties memory;

		struct SwapChainInfo {
			vk::SurfaceCapabilitiesKHR capabilities;
			std::vector<vk::SurfaceFormatKHR> formats;
			std::vector<vk::PresentModeKHR> present_modes;
		} swapchain;

		struct Q {
			uint8_t index;
			vk::QueueFlags type;
			uint8_t count;
			vk::Queue queue;
		};
		struct Queues {
		protected:
			friend Device;
			static constexpr decltype(Q::index) Invalid = std::numeric_limits<decltype(Q::index)>::max() - 1;
			static constexpr auto Required = Invalid;
			static constexpr decltype(Q::index) Ignore = std::numeric_limits<decltype(Q::index)>::max() - 2;
		public:
			Q graphics{ Required, vk::QueueFlagBits::eGraphics };
			Q transfer{ Required, vk::QueueFlagBits::eTransfer };
			Q compute{ Ignore, vk::QueueFlagBits::eCompute };
			Q present{ Required };
		} queue;
	private:
		inline static constexpr bool lambda(const Q& q) { return q.index != Queues::Ignore; }
	public:
		typename decltype(std::views::filter(*reinterpret_cast<std::array<Q, sizeof(Queues) / sizeof(Q)>*>(&queue), &lambda)) queues =
			std::views::filter(*reinterpret_cast<std::array<Q, sizeof(Queues) / sizeof(Q)>*>(&queue), &lambda);

		Device(Context& cxt);
		~Device();

	protected:
		void select_physical();
		void create_logical();
		void get_queues();

		bool is_device_suitable(const vk::PhysicalDevice& device);
	};

}
