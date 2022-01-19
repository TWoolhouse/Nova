#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "swapchain.h"
#include "mlb/mlb.h"

namespace Nova::abyss::vkn {

	Swapchain::Swapchain(Context& cxt, Device& device, const unsigned int width, const unsigned int height) : cxt(cxt), device(device),
		format(), present_mode(vk::PresentModeKHR::eFifo) {
		nvk_tracec("Swapchain");

		bool found = false;
		for (const auto& format : device.formats) {
			if (format.format == vk::Format::eR8G8B8A8Unorm && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
				found = true;
				this->format = format;
				break;
			}
		}

		if (!found) {
			nova_bark_debug("VK Swapchain Format Default: Unavailable");
			this->format = device.formats.front();
		}

		if (std::ranges::find(device.present_modes, vk::PresentModeKHR::eMailbox) != device.present_modes.cend()) {
			this->present_mode = vk::PresentModeKHR::eMailbox;
		} nova_debug_exc(else { nova_bark_debug("VK Present Mode: Mailbox Unavailable"); })

		vk::Extent2D extent{ width, height };
		if (device.capabilities.currentExtent.width == std::numeric_limits<decltype(extent.width)>::max()) {
			extent.width = mlb::clamp(extent.width, device.capabilities.minImageExtent.width, device.capabilities.maxImageExtent.width);
			extent.height = mlb::clamp(extent.height, device.capabilities.minImageExtent.height, device.capabilities.maxImageExtent.height);
		}
		else {
			extent = device.capabilities.currentExtent;
		}

		constexpr auto IMAGES = 3u;
		unsigned int image_count = mlb::clamp(IMAGES, device.capabilities.minImageCount, device.capabilities.maxImageCount ? device.capabilities.maxImageCount : IMAGES);

		std::vector<unsigned int> qfamily_indices;
		if (device.queue.graphics.index != device.queue.present.index) {
			qfamily_indices.reserve(2);
			qfamily_indices.push_back(device.queue.graphics.index);
			qfamily_indices.push_back(device.queue.present.index);
		}

		vk::CompositeAlphaFlagBitsKHR alpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		for (const auto& a : { vk::CompositeAlphaFlagBitsKHR::ePreMultiplied, vk::CompositeAlphaFlagBitsKHR::ePostMultiplied, vk::CompositeAlphaFlagBitsKHR::eInherit }) {
			if (device.capabilities.supportedCompositeAlpha & a) {
				alpha = a;
				break;
			}
		}

		vk::SwapchainCreateInfoKHR create_info(
			vk::SwapchainCreateFlagsKHR(),
			cxt.surface,
			image_count,
			format.format, format.colorSpace,
			extent,
			1, // imageArrayLayers?
			vk::ImageUsageFlagBits::eColorAttachment,
			(qfamily_indices.empty() ? vk::SharingMode::eExclusive : vk::SharingMode::eConcurrent),
			qfamily_indices,
			device.capabilities.currentTransform,
			alpha,
			present_mode,
			true, // TODO: What is this!
			nullptr // OldChain
		);

		handle = device.logical.createSwapchainKHR(create_info, cxt.alloc);

	}

	Swapchain::~Swapchain() {
		nvk_traced("Swapchain");
		device.logical.destroySwapchainKHR(handle, cxt.alloc);
	}

	Image& Swapchain::acquire_next_image(const uint64_t timeout) {
		const auto index = device.logical.acquireNextImageKHR(handle, timeout);
		if (index.result == vk::Result::eErrorOutOfDateKHR) {
			// TODO
		}
		nova_assert(index.result == vk::Result::eSuccess || index.result == vk::Result::eSuboptimalKHR, "[VK] Failed to acquire swapchain image");

		return images[index.value];
	}

}

#endif // NOVA_ABYSS_VULKAN
