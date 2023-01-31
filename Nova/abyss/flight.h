#pragma once
#include "meta/head.h"
#include "cmd_queue.h"

namespace Nova::abyss {

	struct Flight {
		// FIXME: Refactor w/ tower
		// TODO: Flight index
		CommandQueue commands;
	};

} // namespace Nova::abyss
