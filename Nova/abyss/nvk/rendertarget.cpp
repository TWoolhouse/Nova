#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "rendertarget.h"
#include "abyss/renderpass.h"
#include "context.h"

namespace Nova::abyss::nvk {

	RenderTarget::RenderTarget(const Renderpass& renderpass, vk::ImageView& image) :
		self(nova_abyss_api->dev.createFramebuffer(vk::FramebufferCreateInfo{
			.renderPass = renderpass,
			.attachmentCount = 1, // Only 1 attachment in the renderpass
			.pAttachments = &image,
			.width = nova_abyss_app->framesize.width(),
			.height = nova_abyss_app->framesize.height(),
			.layers = 1,
		}, nova_abyss_api->alloc))
	{}

	RenderTarget::~RenderTarget() {
		nova_bark_term("VK RenderTarget");
		nova_abyss_api->dev.destroyFramebuffer(self, nova_abyss_api->alloc);
	}

}

#endif // NOVA_ABYSS_VULKAN
