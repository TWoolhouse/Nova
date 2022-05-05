#pragma once
#include "vk.h"
#include "context.h"
#include "device.h"
#include "swapchain.h"
#include "renderpass.h"
#include "cmd_buffer.h"

namespace Nova::abyss::vkn {

	class Application {
	public:
		static Application* I;
		Context cxt;
		Device device;
		Swapchain swapchain;

		RenderPass renderpass;

		std::vector<vk::Framebuffer> framebuffers;
		vk::CommandPool cmd_pool;

		vk::CommandBuffer buf;

		vk::Semaphore image_available, render_done;
		vk::Fence in_flight;

		//CommandPool pool;

		Application(const std::string_view& name);
		~Application();

		bool active = false;
		NODISCARD bool& acquire();
		NODISCARD void  release();

	protected:
		void recreate_swapchain();
	};

}

#define App ::Nova::abyss::vkn::Application::I

#define __n_vk__app App
#define __n_vk__device App ## ->device.logical
#define __n_vk__alloc App ## ->cxt.alloc

#define nvk(attr) CONCAT(__n_vk__, attr)
