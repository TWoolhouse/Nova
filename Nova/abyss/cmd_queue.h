#pragma once
#include "meta/head.h"
#include "spec/cmd_queue.h"

#if defined(NOVA_ABYSS_VULKAN)
#include "nvk/vk.h"
// #include "nvk/command_buffer.h"
#endif // NOVA_ABYSS

namespace Nova::abyss {

	using CommandQueue =
	#if defined(NOVA_ABYSS_VULKAN)
	vk::CommandBuffer;
	//nvk::CommandBuffer;
	#else
	spec::null;
	#endif // NOVA_ABYSS

	static_assert(spec::CommandQueue<CommandQueue>, "CommandQueue invalidated the Spec");

} // namespace Nova::abyss
