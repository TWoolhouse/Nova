#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "app.h"
#include "core/application.h"

#include "renderpass.h"
#include "shader_test.h"

namespace Nova::abyss::vkn {

	decltype(Application::I) Application::I;

	static vk::PipelineLayout layout;
	static vk::Pipeline pipeline;

	Application::Application(const std::string_view& name)
		: cxt(name), device(cxt),
		swapchain(cxt, device, nova_app->window.width(), nova_app->window.height()),
		renderpass(device, swapchain) {
		nova_assert(!I, "Creating Multiple Vulkan Applications!");
		I = this;

		{ // Framebuffers
			nvk_tracec("Framebuffers");
			framebuffers.reserve(swapchain.images.size());
			for (auto& view : swapchain.views) {
				const std::array<vk::ImageView, 1> views{ view };
				vk::FramebufferCreateInfo create_info{
					.renderPass = renderpass.pass,
					.attachmentCount = views.size(),
					.pAttachments = views.data(),
					.width = swapchain.extent.width,
					.height = swapchain.extent.height,
					.layers = 1,
				};
				framebuffers.emplace_back(device.logical.createFramebuffer(create_info, nvk(alloc)));
			}
		}

		{ // Graphics Pipeline
			auto p = create_pipeline(renderpass);
			layout = p.first; pipeline = p.second;
		}

		{ // Command Pool
			nvk_tracec("Command Pool");
			vk::CommandPoolCreateInfo create_info{
				.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
				.queueFamilyIndex = device.queue.graphics.index,
			};
			cmd_pool = device.logical.createCommandPool(create_info, nvk(alloc));
		}

		{ // Command Buffer
			nvk_tracec("Command Buffer");
			vk::CommandBufferAllocateInfo info{
				.commandPool = cmd_pool,
				.level = vk::CommandBufferLevel::ePrimary,
				.commandBufferCount = 1,
			};
			auto v = device.logical.allocateCommandBuffers(info);
			buf = v[0];
		}

		{ // Semaphore & Fences
			nvk_tracec("Semaphores & Fences");
			image_available = device.logical.createSemaphore({}, nvk(alloc));
			render_done = device.logical.createSemaphore({}, nvk(alloc));
			in_flight = device.logical.createFence(vk::FenceCreateInfo{
				.flags = vk::FenceCreateFlagBits::eSignaled
			}, nvk(alloc));
		}

	}
	Application::~Application() {
		nvk_traced("Application");

		device.logical.waitIdle();

		{
			nvk_traced("Semaphores & Fences");
			device.logical.destroySemaphore(image_available, nvk(alloc));
			device.logical.destroySemaphore(render_done, nvk(alloc));
			device.logical.destroyFence(in_flight, nvk(alloc));
		}

		{
			nvk_traced("Command Pool");
			device.logical.destroyCommandPool(cmd_pool, nvk(alloc));
		}

		{
			nvk_traced("Framebuffers");
			for (auto& fb : framebuffers) {
				device.logical.destroyFramebuffer(fb, nvk(alloc));
			}
		}

		{
			nvk_traced("Pipeline");
			nvk(device).destroyPipeline(pipeline, nvk(alloc));
			nvk(device).destroyPipelineLayout(layout, nvk(alloc));
		}
		// I = nullptr; // In vk_abyss.cpp
	}

	bool& Application::acquire() {
		active = true;

		//nova_bark_debug("Waiting for Fence");
		if (device.logical.waitForFences(in_flight, VK_TRUE, UINT64_MAX) == vk::Result::eTimeout) {
			nova_bark_error("Failed to Wait for Fence");
			active = false;
			return active;
		}

		const auto image = swapchain.acquire_next_image(UINT64_MAX, image_available);

		device.logical.resetFences(in_flight);

		buf.reset();
		vk::CommandBufferBeginInfo begin{};
		buf.begin(begin);

		vk::ClearValue cv = {
			.color = vk::ClearColorValue(std::array<float, 4>({ 0.0f, 0.0f, 0.0f, 1.0f }))
		};
		vk::RenderPassBeginInfo rpinfo{
			.renderPass = renderpass.pass,
			.framebuffer = framebuffers[image],
			.renderArea = { {}, swapchain.extent },
			.clearValueCount = 1,
			.pClearValues = &cv,
		};

		buf.beginRenderPass(rpinfo, vk::SubpassContents::eInline);
		buf.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);

		buf.draw(3, 1, 0, 0);

		buf.endRenderPass();

		buf.end();

		const std::vector<vk::Semaphore> wait_sems = { image_available };
		const vk::PipelineStageFlags dst = { vk::PipelineStageFlagBits::eColorAttachmentOutput };

		vk::SubmitInfo info{
			.waitSemaphoreCount = static_cast<uint32_t>(wait_sems.size()),
			.pWaitSemaphores = wait_sems.data(),
			.pWaitDstStageMask = &dst,
			.commandBufferCount = 1,
			.pCommandBuffers = &buf,
			.signalSemaphoreCount = 1,
			.pSignalSemaphores = &render_done,
		};
		device.queue.graphics.queue.submit(info, in_flight);

		vk::PresentInfoKHR present{
			.waitSemaphoreCount = 1,
			.pWaitSemaphores = &render_done,
			.swapchainCount = 1,
			.pSwapchains = &swapchain.swapchain,
			.pImageIndices = &image,
		};
		device.queue.present.queue.presentKHR(present);

		return active;
	}

	void Application::release() {
		if (!active) return;
		active = false;
	}

	void Application::recreate_swapchain() {
		swapchain = Swapchain(swapchain, nova_app->window.width(), nova_app->window.height());
	}

}

#endif // NOVA_ABYSS_DEBUG
