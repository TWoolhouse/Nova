#pragma once
#include "meta/head.h"
#include "vk.h"

namespace Nova::abyss::nvk {

	struct Renderpass;

	struct RenderTarget : OPVK<RenderTarget, vk::Framebuffer> {
		vk::Framebuffer self;
		RenderTarget(const Renderpass& renderpass, vk::ImageView& image);
		~RenderTarget();
	};

}
