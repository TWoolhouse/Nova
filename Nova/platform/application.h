#pragma once
#include "meta/head.h"
#include "core/window.h"

namespace Nova {

	namespace core {
		class Application;
	}

	namespace platform {
		void Initialize(const std::string_view& name, const core::Window& window);
		void Termintate();
		void process_events();
	}
}
