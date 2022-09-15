#pragma once
#include "meta/head.h"
#include "../flight.h"
#include "sync.h"
#include "context/swapchain.h"

namespace Nova::abyss::nvk {

	struct Flight : public abyss::Flight {
		struct Sync {
			Fence in_flight;
			Semaphore image_avalible;
			Semaphore render_done;
		} sync;
		struct Command {
			vk::CommandPool pool;
			vk::CommandBuffer buffer;

			Command();
			~Command();
		} cmd;
		Swapchain::FrameIndex swapchain_frame_index;
		Flight();
	};

}
