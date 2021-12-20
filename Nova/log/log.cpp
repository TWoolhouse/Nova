#include "npch.h"
#include "log.h"

#include <iostream>

namespace Nova::Bark {

	void Initialize() {
		NOVA_BARK_INFO("Nova Bark Initialized");
	}
	void Terminate() {
		NOVA_BARK_INFO("Nova Bark Terminated");
	}

	void submit(Level level, const std::string& msg) {
		static constexpr std::string_view levels[static_cast<char>(Level::MAX)] = {"Debug", "Info", "Warn", "Error", "Fatal"};
		(level < Level::Error ? std::cout : std::cerr) << levels[static_cast<char>(level)] << ": " << msg << std::endl;
	}

}
