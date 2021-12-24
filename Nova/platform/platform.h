#pragma once
#include "defines.h"

namespace Nova {
	class platform {
		friend class Application;
	protected:
		static void Initialize(const std::string_view& name, const unsigned int width, const unsigned int height);
		static void Termintate();
	public:
		static void pump_messages();

	};
}
