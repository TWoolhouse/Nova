#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "renderpass.h"
#include "context.h"

namespace Nova::abyss::nvk {

	Renderpass::Renderpass() :
		self(VK_NULL_HANDLE),
		event_ticket(event::dispatcher.subscribe(event::Type::WindowResizeFrame, [&](event::Handle&) {
			target.clear();
			create_targets();
			return true;
		}))
	{
		nova_bark_init("VK Renderpass");

		vk::AttachmentDescription atmt_colour{
			.format = nova_abyss_api->swapchain.format,
			.samples = vk::SampleCountFlagBits::e1,
			.loadOp = vk::AttachmentLoadOp::eClear,
			.storeOp = vk::AttachmentStoreOp::eStore,
			.stencilLoadOp = vk::AttachmentLoadOp::eDontCare,
			.stencilStoreOp = vk::AttachmentStoreOp::eDontCare,
			.initialLayout = vk::ImageLayout::eUndefined,
			.finalLayout = vk::ImageLayout::ePresentSrcKHR,
		};
		vk::AttachmentReference atmt_ref_colour{
			.attachment = 0,
			.layout = vk::ImageLayout::eColorAttachmentOptimal,
		};

		// TODO: Depth Stencil Attachment

		vk::SubpassDescription subpass{
			.pipelineBindPoint = vk::PipelineBindPoint::eGraphics,
			.colorAttachmentCount = 1,
			.pColorAttachments = &atmt_ref_colour,
		};

		//vk::SubpassDependency subpass_order{
		//	.srcSubpass = VK_SUBPASS_EXTERNAL,
		//	.dstSubpass = 0,
		//};

		vk::RenderPassCreateInfo info_renderpass{
			.attachmentCount = 1,
			.pAttachments = &atmt_colour,
			.subpassCount = 1,
			.pSubpasses = &subpass,
			//.dependencyCount = 1,
			//.pDependencies = nullptr,
		};

		self = NVK_CHECK(nova_abyss_api->dev.createRenderPass(info_renderpass, nova_abyss_api->alloc), "Failed to create Renderpass!");
		create_targets();
	}

	Renderpass::~Renderpass() {
		nova_bark_term("VK Renderpass");
		nova_abyss_api->dev.destroyRenderPass(self, nova_abyss_api->alloc);
	}

	void Renderpass::create_targets() {
		target.reserve(nova_abyss_api->swapchain.frames.size());
		nova_bark_init("VK RenderTarget: {}", nova_abyss_api->swapchain.frames.size());
		for (auto& frame : nova_abyss_api->swapchain.frames) {
			target.emplace_back(*this, frame.view);
		}
	}

}

#endif // NOVA_ABYSS_VULKAN
