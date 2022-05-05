#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "renderpass.h"
#include "app.h"

namespace Nova::abyss::vkn {

	RenderPass::RenderPass(Device& device, Swapchain& swapchain) {
		nvk_tracec("RenderPass");
		const vk::AttachmentDescription atm_colour{
			{},
			swapchain.format.format,
			vk::SampleCountFlagBits::e1,
			vk::AttachmentLoadOp::eClear, // Clear to black first
			vk::AttachmentStoreOp::eStore, // Store because we need it
			vk::AttachmentLoadOp::eDontCare, // Stencil, not using it yet
			vk::AttachmentStoreOp::eDontCare,
			vk::ImageLayout::eUndefined, // Doesn't matter as we are clearing it anyway
			vk::ImageLayout::ePresentSrcKHR, // Need to present
		};

		vk::AttachmentReference colour_ref{
			0,
			vk::ImageLayout::eColorAttachmentOptimal
		};

		const std::array<vk::AttachmentReference, 1> sub_refs{ colour_ref };
		vk::SubpassDescription subpass{
			{},
			vk::PipelineBindPoint::eGraphics,
			{},
			sub_refs,
		};

		const std::array<vk::AttachmentDescription, 1> attachments{ atm_colour };
		const std::array<vk::SubpassDescription, 1> subpasses{ subpass };

		vk::SubpassDependency dep{
			VK_SUBPASS_EXTERNAL,
			0,
			vk::PipelineStageFlagBits::eColorAttachmentOutput,
			vk::PipelineStageFlagBits::eColorAttachmentOutput,
			vk::AccessFlagBits{0},
			vk::AccessFlagBits::eColorAttachmentWrite
		};

		vk::RenderPassCreateInfo create_info{
			{},
			attachments,
			subpasses,
			dep
		};

		pass = device.logical.createRenderPass(create_info, device.cxt.alloc);

	}

	RenderPass::~RenderPass() {
		nvk_traced("RenderPass");
		nvk(device).destroyRenderPass(pass, nvk(alloc));
	}

}
#endif // NOVA_ABYSS_VULKAN
