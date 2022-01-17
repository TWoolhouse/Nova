#pragma once
#include "meta/head.h"

namespace Nova {

	namespace core {
		class Application;
	}

	class platform {
		friend core::Application;
	protected:
		static void Initialize(const std::string_view& name, const unsigned int width, const unsigned int height);
		static void Termintate();
		static void process_events();
	};
}
