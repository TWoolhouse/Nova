#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"
#include "swapchain.h"
#include "context.h"
#include "abyss/exc/frame_resize.h"

#include "event/window.h"

namespace Nova::abyss::nvk {

	void log_swapchain(const vk::SwapchainCreateInfoKHR& info, const vk::SurfaceCapabilitiesKHR& cap, const size_t& image_count) {
		if constexpr (Nova::bark::def::info) {
			nova_bark_info("\tPresent Mode: {}", info.presentMode);
			nova_bark_info("\tBuffering Count: {} <= {} <= {}", cap.minImageCount, image_count, cap.maxImageCount);
			nova_bark_info("\tFormat: {}", info.imageFormat);
			nova_bark_info("\tColour Space: {}", info.imageColorSpace);
			nova_bark_info("\tFramebuffer Size: ({}, {}) px", info.imageExtent.width, info.imageExtent.height);

			nova_bark_info("\tQueue Family Sharing: {}", info.imageSharingMode);
			if (info.imageSharingMode == vk::SharingMode::eConcurrent) {
				std::stringstream stream;
				for (uint32_t i = 0; i < info.queueFamilyIndexCount; ++i) {
					stream << " " << info.pQueueFamilyIndices[i];
				}
				nova_bark_info("\t\tFamilies:{}", stream.str());
			}
		}
	}

	Swapchain::Swapchain() :
		self(VK_NULL_HANDLE),
		format(nova_abyss_api->device.info.swapchain.format.format),
		frames()
	{
		nova_bark_init("VK Swapchain");
		shared_families();
		create();
	}

	Swapchain::~Swapchain() {
		nova_bark_term("VK Swapchain");
		frames.clear(); // Make sure the image views are destructed first
		nova_abyss_api->dev.destroySwapchainKHR(self, nova_abyss_api->alloc);
	}
	Swapchain::FrameImage::~FrameImage() {
		nova_abyss_api->dev.destroyImageView(view, nova_abyss_api->alloc);
	}

	bool Swapchain::create() {
		auto capabilities = nova_abyss_api->device.physical.getSurfaceCapabilitiesKHR(nova_abyss_api->instance.surface);

		// Minimised and there is invalid to attempt to create the swapchain.
		if (capabilities.currentExtent == vk::Extent2D{ 0, 0 }) return false;

		nova_assert(revalidate_format(nova_abyss_api->device.info.swapchain.format), "The surface format has changed since selecting the physical device!");
		nova_assert(revalidate_present_mode(nova_abyss_api->device.info.swapchain.present_mode), "The surface present mode has changed since selecting the physical device!");

		vk::SwapchainCreateInfoKHR info_swapchain{
			.surface = nova_abyss_api->instance.surface,
			.minImageCount = IMAGE_BUFFERING,
			.imageFormat = nova_abyss_api->device.info.swapchain.format.format,
			.imageColorSpace = nova_abyss_api->device.info.swapchain.format.colorSpace,
			.imageExtent = extent(capabilities),
			.imageArrayLayers = 1,
			.imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
			.imageSharingMode = nova_abyss_api->device.info.swapchain.image_sharing.size() > 1 ? vk::SharingMode::eConcurrent : vk::SharingMode::eExclusive,
			.queueFamilyIndexCount = static_cast<uint32_t>(nova_abyss_api->device.info.swapchain.image_sharing.size()),
			.pQueueFamilyIndices = nova_abyss_api->device.info.swapchain.image_sharing.data(),
			.preTransform = capabilities.currentTransform,
			.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque,
			.presentMode = nova_abyss_api->device.info.swapchain.present_mode,
			.clipped = VK_TRUE,
			.oldSwapchain = self,
		};

		self = NVK_CHECK(nova_abyss_api->dev.createSwapchainKHR(info_swapchain, nova_abyss_api->alloc), "Failed to create Swapchain!");
		nova_abyss_app->framesize.size(info_swapchain.imageExtent.width, info_swapchain.imageExtent.height);
		format = info_swapchain.imageFormat;
		extract_images();

		log_swapchain(info_swapchain, capabilities, frames.size());
		return true;
	}

	void Swapchain::resize() {
		nova_abyss_api->queues.graphics.self.waitIdle();
		frames.clear();
		if (create()) {
			nova_bark_trace("Swapchain Resized!");
			Nova::event::WindowResizeFrame(nova_abyss_app->framesize.width(), nova_abyss_app->framesize.height()).fire();
		}
	}

	// Get the images & views from the swapchain
	void Swapchain::extract_images() {
		auto images = nova_abyss_api->dev.getSwapchainImagesKHR(self);
		frames.reserve(images.size());
		for (auto&& image : images) {
			vk::ImageViewCreateInfo info_view{
				.image = image,
				.viewType = vk::ImageViewType::e2D,
				.format = format,
				.subresourceRange = { vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 },
			};
			frames.emplace_back(
				image,
				NVK_CHECK(nova_abyss_api->dev.createImageView(info_view, nova_abyss_api->alloc), "Failed to create Swapchain Image View!")
			);
		}
	}

	Swapchain::FrameIndex Swapchain::acquire_frame(Fence& in_flight, Semaphore& image_avalible) {
		// FIXME: Hardcoded Timeout, make part of the build
		constexpr size_t TIME_OUT = 0.25e+9; // Nanoseconds

		// Wait until the flight has finished rendering and is free again
		// FIXME: Read return value
		nova_abyss_api->dev.waitForFences(reinterpret_cast<vk::Fence&>(in_flight), VK_TRUE, TIME_OUT);

		try {
			auto frame = nova_abyss_api->dev.acquireNextImageKHR(self, TIME_OUT, image_avalible);
			//nova_bark_debug("Acquire Image: {} {}", frame.value, frame.result);
			switch (frame.result) {
				case vk::Result::eSuccess:	return frame.value;
				case vk::Result::eSuboptimalKHR:
					this->resize();
					throw exc::FrameResize{};
			default:
				throw std::runtime_error{ "Unable to acquire next swapchain image!" };
			}
		} catch (const vk::OutOfDateKHRError&) {
			this->resize();
			throw exc::FrameResize{};
		}
	}

	vk::Extent2D Swapchain::extent(const vk::SurfaceCapabilitiesKHR& capabilities) {
		if (capabilities.currentExtent != vk::Extent2D{ 0xFFFFFFFF, 0xFFFFFFFF })
			return capabilities.currentExtent;

		auto& [width, height] = nova_abyss_app->framesize.size();
		return vk::Extent2D {
			std::clamp(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width),
			std::clamp(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height),
		};
	}

	void Swapchain::shared_families() {
		for (auto&& queue : { nova_abyss_api->queues.present, nova_abyss_api->queues.graphics })
			if (auto it = std::ranges::find(nova_abyss_api->device.info.swapchain.image_sharing, queue.family); it == nova_abyss_api->device.info.swapchain.image_sharing.end())
				nova_abyss_api->device.info.swapchain.image_sharing.emplace_back(queue.family);
	}

	bool Swapchain::revalidate_format(const vk::SurfaceFormatKHR& format) {
		auto formats = nova_abyss_api->device.physical.getSurfaceFormatsKHR(nova_abyss_api->instance.surface);
		auto it = std::ranges::find(formats, format);
		return it != formats.end();
	}

	bool Swapchain::revalidate_present_mode(const vk::PresentModeKHR& present_mode) {
		auto present_modes = nova_abyss_api->device.physical.getSurfacePresentModesKHR(nova_abyss_api->instance.surface);
		auto it = std::ranges::find(present_modes, present_mode);
		return it != present_modes.end();
	}

}

#endif // NOVA_ABYSS_VULKAN
