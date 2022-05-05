#pragma once
#include "vk.h"
#include "context.h"
#include "swapchain.h"
#include "device.h"

namespace Nova::abyss::vkn {

	class RenderPass {
	public:
		vk::RenderPass pass;
		RenderPass(Device& device, Swapchain& swapchain);
		~RenderPass();
	};

}