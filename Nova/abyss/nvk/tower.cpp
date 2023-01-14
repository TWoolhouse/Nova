#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "tower.h"
#include "context.h"
#include "abyss/exc/frame_resize.h"

namespace Nova::abyss::nvk {

	Tower::Tower() :
		renderpass()
	{
		nova_bark_init("Abyss Tower");
	}
	Tower::~Tower() {
		nova_bark_term("Abyss Tower");
		nova_abyss_api->queues.graphics.self.waitIdle();
		nova_abyss_api->queues.present.self.waitIdle();
	}

	abyss::Flight& Tower::acquire() {
		auto& flight = next_flight();
		flight.swapchain_frame_index = nova_abyss_api->swapchain.acquire_frame(flight.sync.in_flight, flight.sync.image_avalible);
		nova_abyss_api->dev.resetFences(flight.sync.in_flight.self);
		auto& target = renderpass.target[flight.swapchain_frame_index];

		nova_abyss_api->dev.resetCommandPool(flight.cmd.pool);
		main_pass_begin(flight);
		sub_buffer_begin(flight);

		return flight;
	}

	void Tower::release(Flight& flight) {
		sub_buffer_end(flight);
		main_pass_end(flight);

		submit(flight);
	}

	void Tower::submit(Flight& flight) {
		vk::PipelineStageFlags wait_dst = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		nova_abyss_api->queues.graphics.self.submit(vk::SubmitInfo{
			.waitSemaphoreCount = 1,
			.pWaitSemaphores = &flight.sync.image_avalible.self,
			.pWaitDstStageMask = &wait_dst,
			.commandBufferCount = 1,
			.pCommandBuffers = &flight.cmd.buffer,
			.signalSemaphoreCount = 1,
			.pSignalSemaphores = &flight.sync.render_done.self,
		}, flight.sync.in_flight);

		uint32_t image_index = flight.swapchain_frame_index;
		try {
			switch (nova_abyss_api->queues.present.self.presentKHR(vk::PresentInfoKHR{
				.waitSemaphoreCount = 1,
				.pWaitSemaphores = &flight.sync.render_done.self,
				.swapchainCount = 1,
				.pSwapchains = &nova_abyss_api->swapchain.self,
				.pImageIndices = &image_index,
			})) {
				case vk::Result::eSuccess:
				case vk::Result::eSuboptimalKHR:
					return;
			}
		} catch (const vk::OutOfDateKHRError& e) {
			nova_abyss_api->swapchain.resize();
			throw exc::FrameResize{};
		}
	}

	Flight& Tower::next_flight() {
		auto& flight = flights[current_flight];
		current_flight = (current_flight + 1) % MAX_FLIGHTS;
		return flight;
	}

	void Tower::main_pass_begin(Flight& flight) {
		flight.cmd.buffer.begin(vk::CommandBufferBeginInfo{
			.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit,
		});

		vk::ClearValue clear_value = {
			.color = vk::ClearColorValue(std::array<float, 4>({ 0.0f, 0.0f, 0.0f, 1.0f }))
		};
		flight.cmd.buffer.beginRenderPass(vk::RenderPassBeginInfo{
			.renderPass = renderpass,
			.framebuffer = renderpass.target[flight.swapchain_frame_index],
			.renderArea = { {}, { nova_abyss_app->framesize.width(), nova_abyss_app->framesize.height() } },
			.clearValueCount = 1,
			.pClearValues = &clear_value,
		}, vk::SubpassContents::eSecondaryCommandBuffers);
	}

	void Tower::main_pass_end(Flight& flight) {
		flight.cmd.buffer.executeCommands(flight.commands.self);
		flight.cmd.buffer.endRenderPass();
		flight.cmd.buffer.end();
	}

	void Tower::sub_buffer_begin(Flight& flight) {
		vk::CommandBufferInheritanceInfo info_inheritance{
			.renderPass = renderpass,
			.subpass = 0,
			.framebuffer = renderpass.target[flight.swapchain_frame_index],
		};
		flight.commands.self.begin(vk::CommandBufferBeginInfo{
			.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit | vk::CommandBufferUsageFlagBits::eRenderPassContinue,
			.pInheritanceInfo = &info_inheritance,
		});
	}

	void Tower::sub_buffer_end(Flight& flight) {
		flight.commands.self.end();
	}

}

#endif // NOVA_ABYSS_VULKAN
