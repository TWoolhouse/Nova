#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "swapchain.h"
#include "mlb/mlb.h"

constexpr auto IMAGES = 3u;

namespace Nova::abyss::vkn {

	Swapchain::Swapchain(Context& cxt, Device& device, const unsigned int width, const unsigned int height)
		: cxt(cxt), device(device), extent(width, height), format(), present_mode(vk::PresentModeKHR::eFifo) {
		nvk_tracec("Swapchain");

		init(generate_info());
	}

	Swapchain::Swapchain(const Swapchain& swapchain, const unsigned int width, const unsigned int height)
		: cxt(swapchain.cxt), device(swapchain.device),
		extent(width, height), format(swapchain.format), present_mode(swapchain.present_mode) {
		nvk_trace("Swapchain", "Recreating", "Recreated");

		auto info = generate_info();
		info.setOldSwapchain(swapchain.swapchain);
		init(info);
	}

	Swapchain& Swapchain::operator=(Swapchain&& swapchain) noexcept {
		if (this != &swapchain) {
			nvk_trace("Swapchain", "Moving", "Moved");
			std::swap(views, swapchain.views);
			std::swap(images, swapchain.images);
			std::swap(extent, swapchain.extent);
			std::swap(format, swapchain.format);
			std::swap(present_mode, swapchain.present_mode);
		} return *this;
	}

	vk::SwapchainCreateInfoKHR Swapchain::generate_info() noexcept {
		choose_format();
		choose_present_mode();
		choose_extent();

		unsigned int image_count = mlb::clamp(IMAGES, device.capabilities.minImageCount, device.capabilities.maxImageCount ? device.capabilities.maxImageCount : IMAGES);
		nova_bark_info("Swapchain Images: {} <= {} <= {}", device.capabilities.minImageCount, image_count, device.capabilities.maxImageCount);

		std::vector<unsigned int> qfamily_indices;
		if (device.queue.graphics.index != device.queue.present.index) {
			qfamily_indices.reserve(2);
			qfamily_indices.push_back(device.queue.graphics.index);
			qfamily_indices.push_back(device.queue.present.index);
		}

		return {
			{},
			cxt.surface,
			image_count,
			format.format, format.colorSpace,
			extent,
			1, // imageArrayLayers?
			vk::ImageUsageFlagBits::eColorAttachment,
			(qfamily_indices.empty() ? vk::SharingMode::eExclusive : vk::SharingMode::eConcurrent),
			qfamily_indices,
			device.capabilities.currentTransform,
			choose_alpha(),
			present_mode,
			true, // Always Clip
			nullptr // OldChain
		};
	}

	void Swapchain::init(const vk::SwapchainCreateInfoKHR& info) {
		swapchain = device.logical.createSwapchainKHR(info, cxt.alloc);
		images = device.logical.getSwapchainImagesKHR(swapchain);

		views.reserve(images.size());

		for (const auto& image : images) {
			views.push_back(device.logical.createImageView({
				{},
				image,
				vk::ImageViewType::e2D,
				format.format,
				{},
				{ vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 }
				}, cxt.alloc));
		}

		// const auto depth_format = this->depth_format();
		// if (depth_format == vk::Format::eUndefined) {
		// 	nova_bark_fatal("No Depth format!");
		// }

	}

	Swapchain::~Swapchain() {
		nvk_traced("Swapchain");

		for (auto& view : views) {
			device.logical.destroyImageView(view, cxt.alloc);
		}
		views.clear();

		device.logical.destroySwapchainKHR(swapchain, cxt.alloc);
	}

	uint32_t Swapchain::acquire_next_image(const uint64_t timeout, vk::Semaphore& semaphore) {
		const auto index = device.logical.acquireNextImageKHR(swapchain, timeout, semaphore);
		switch (index.result) {
			case vk::Result::eSuboptimalKHR:
				break;
			case vk::Result::eErrorOutOfDateKHR:
				break;
			default:
				nova_assert(index.result == vk::Result::eSuccess, "[VK] Failed to acquire swapchain image");
				return index.value;
		}
		nova_bark_debug("Swapchain State: {}", index.result);

		return index.value;
	}

	void Swapchain::choose_format() {
		if (const auto fmt = std::ranges::find_if(device.formats, [](const auto& fmt) { return fmt.format == vk::Format::eB8G8R8A8Srgb && fmt.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear; }
		); fmt != device.formats.cend()) {
			format = *fmt;
			return;
		}
		format = device.formats.front();
		nova_bark_debug("VK Swapchain Format BGRA_Srgb-SrgbNL is Unavailable");
	}

	constexpr void Swapchain::choose_present_mode() {
		if (std::ranges::find(device.present_modes, vk::PresentModeKHR::eMailbox) != device.present_modes.cend()) {
			present_mode = vk::PresentModeKHR::eMailbox;
			nova_bark_info("Present Mode: Mailbox");
			return;
		}
		else if (std::ranges::find(device.present_modes, vk::PresentModeKHR::eFifoRelaxed) != device.present_modes.cend()) {
			present_mode = vk::PresentModeKHR::eFifoRelaxed;
			nova_bark_info("Present Mode: FifoRelaxed");
			return;
		}

		present_mode = vk::PresentModeKHR::eFifo;
		nova_bark_info("Present Mode: Fifo");

	}

	constexpr void Swapchain::choose_extent() {
		if (device.capabilities.currentExtent.width == std::numeric_limits<decltype(extent.width)>::max()) {
			extent.width = mlb::clamp(extent.width, device.capabilities.minImageExtent.width, device.capabilities.maxImageExtent.width);
			extent.height = mlb::clamp(extent.height, device.capabilities.minImageExtent.height, device.capabilities.maxImageExtent.height);
		}
		else {
			extent = device.capabilities.currentExtent;
		}
	}

	constexpr vk::CompositeAlphaFlagBitsKHR Swapchain::choose_alpha() {
		for (const auto& a : { vk::CompositeAlphaFlagBitsKHR::ePreMultiplied, vk::CompositeAlphaFlagBitsKHR::ePostMultiplied, vk::CompositeAlphaFlagBitsKHR::eInherit }) {
			if (device.capabilities.supportedCompositeAlpha & a) {
				return a;
			}
		}
		return vk::CompositeAlphaFlagBitsKHR::eOpaque;
	}

	vk::Format Swapchain::depth_format() {
		constexpr std::array candidates{
			vk::Format::eD32Sfloat,
			vk::Format::eD32SfloatS8Uint,
			vk::Format::eD24UnormS8Uint,
		};
		constexpr auto flags = vk::FormatFeatureFlagBits::eDepthStencilAttachment;
		for (const auto& candidate : candidates) {
			const auto properties = device.physical.getFormatProperties(candidate);
			if ((properties.linearTilingFeatures & flags) == flags)
				return candidate;
			else if ((properties.optimalTilingFeatures & flags) == flags)
				return candidate;
		}
		return vk::Format::eUndefined;
	}

}

#endif // NOVA_ABYSS_VULKAN
