#pragma once
#include "vk.h"
#include "setup_props.h"
#include "queues.h"

namespace Nova::abyss::nvk {

	class Device {
	public:
		struct Info {
			Queues queues;
			struct Swapchain {
				vk::SurfaceFormatKHR format;
				vk::PresentModeKHR present_mode;
				std::vector<Q::Index> image_sharing;
			} swapchain;
		} info;
		vk::PhysicalDevice physical;
		vk::Device logical;


		Device(const Setup& properties);
		~Device();
	};

}
