#pragma once
#include "vk.h"
#include "core/info.h"
#include "setup_props.h"
#include "instance.h"
#include "queues.h"
#include "device.h"
#include "vma.h"
#include "swapchain.h"

namespace Nova::abyss::nvk {

	class Context {
	public:
		INLINE constexpr Context* operator->() { return this; }
		vk::AllocationCallbacks* alloc;
		Instance instance;
		Device device;

		Queues& queues;
		vk::Device& dev;

		VMA vma;

		Swapchain swapchain;

		Context(const core::Information& info, const Setup& properties);
		~Context();
	};

}

#include "abyss/app.h"
#define nova_abyss_api ::Nova::abyss::App::I->api
