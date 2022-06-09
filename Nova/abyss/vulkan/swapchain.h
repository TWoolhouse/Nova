#pragma once
#include "vk.h"
#include "image.h"
#include "device.h"

namespace Nova::abyss::vkn {

	class Swapchain {
		friend class Application;
	protected:
		Context& cxt;
		Device& device;
	public:
		vk::SwapchainKHR swapchain;
		std::vector<vk::Image> images;
		std::vector<vk::ImageView> views;

		vk::Extent2D extent;
		vk::SurfaceFormatKHR format;
		vk::PresentModeKHR present_mode;

		uint32_t acquire_next_image(const uint64_t timeout, vk::Semaphore& Semaphore);

		~Swapchain();
	protected:
		Swapchain(Context& cxt, Device& device, const unsigned int width, const unsigned int height);
		Swapchain(const Swapchain& swapchain, const unsigned int width, const unsigned int height);
		Swapchain& operator=(Swapchain&& swapchain) noexcept;
	protected:
		void choose_format();
		constexpr void choose_present_mode();
		constexpr void choose_extent();
		constexpr vk::CompositeAlphaFlagBitsKHR choose_alpha();
		vk::Format depth_format();

		vk::SwapchainCreateInfoKHR generate_info() noexcept;
		void init(const vk::SwapchainCreateInfoKHR& info);
	};

}
