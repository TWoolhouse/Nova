#pragma once
#include "meta/head.h"
#include "core/info.h"
#include "core/window.h"

namespace Nova {

	namespace platform {
		void Initialize(const core::Information& app_info);
		void Termintate();
		void process_events();
	}
}
