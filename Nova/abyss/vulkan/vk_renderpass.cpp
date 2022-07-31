#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "renderpass.h"
#include "app.h"

namespace Nova::abyss::vkn {

	RenderPass::RenderPass(Device& device, Swapchain& swapchain) {
		nvk_tracec("RenderPass");
		const vk::AttachmentDescription atm_colour{
			.format =  swapchain.format.format,
			.samples = vk::SampleCountFlagBits::e1,
			.loadOp = vk::AttachmentLoadOp::eClear, // Clear to black first
			.storeOp = vk::AttachmentStoreOp::eStore, // Store because we need it
			.stencilLoadOp = vk::AttachmentLoadOp::eDontCare, // Stencil, not using it yet
			.stencilStoreOp =  vk::AttachmentStoreOp::eDontCare,
			.initialLayout = vk::ImageLayout::eUndefined, // Doesn't matter as we are clearing it anyway
			.finalLayout = vk::ImageLayout::ePresentSrcKHR, // Need to present
		};

		vk::AttachmentReference colour_ref{
			.attachment = 0,
			.layout = vk::ImageLayout::eColorAttachmentOptimal,
		};

		const std::array<vk::AttachmentReference, 1> sub_refs{ colour_ref };
		vk::SubpassDescription subpass{
			.pipelineBindPoint = vk::PipelineBindPoint::eGraphics,
			.colorAttachmentCount = static_cast<uint32_t>(sub_refs.size()),
			.pColorAttachments = sub_refs.data(),
		};

		const std::array<vk::AttachmentDescription, 1> attachments{ atm_colour };
		const std::array<vk::SubpassDescription, 1> subpasses{ subpass };

		vk::SubpassDependency dep{
			.srcSubpass = VK_SUBPASS_EXTERNAL,
			.dstSubpass = 0,
			.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput,
			.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput,
			.srcAccessMask = vk::AccessFlagBits{0},
			.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite,
		};

		vk::RenderPassCreateInfo create_info{
			.attachmentCount = static_cast<uint32_t>(attachments.size()),
			.pAttachments = attachments.data(),
			.subpassCount = static_cast<uint32_t>(subpasses.size()),
			.pSubpasses = subpasses.data(),
			.dependencyCount = 1,
			.pDependencies = &dep,
		};

		pass = device.logical.createRenderPass(create_info, device.cxt.alloc);

	}

	RenderPass::~RenderPass() {
		nvk_traced("RenderPass");
		nvk(device).destroyRenderPass(pass, nvk(alloc));
	}

}
#endif // NOVA_ABYSS_VULKAN
