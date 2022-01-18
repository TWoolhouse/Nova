#pragma once
#include "vk.h"
#include "image.h"
#include "device.h"

namespace Nova::abyss::vkn {

	class Swapchain {
	protected:
		Context& cxt;
		Device& device;
	public:
		vk::SwapchainKHR handle;
		std::vector<Image> images;

		vk::SurfaceFormatKHR format;
		vk::PresentModeKHR present_mode;

		Swapchain(Context& cxt, Device& device, const unsigned int width, const unsigned int height);
		~Swapchain();

		Image& acquire_next_image(const uint64_t timeout);
	};

}