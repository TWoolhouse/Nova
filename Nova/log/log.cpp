#include "npch.h"
#include "log.h"

#include <iostream>

#ifdef nova_assert
#include <intrin.h>
#endif // nova_assert

namespace Nova::Bark {

	void Initialize() {
		nova_bark_info("Nova Bark Initialized");
	}
	void Terminate() {
		nova_bark_info("Nova Bark Terminated");
	}

	void submit(const Level level, const std::string& msg) {
		static constexpr std::string_view levels[static_cast<char>(Level::MAX)] = {"Debug", "Info", "Warn", "Error", "Fatal"};
		(level < Level::Error ? std::cout : std::cerr) << levels[static_cast<char>(level)] << ": " << msg << std::endl;
	}

	#ifdef nova_assert
	void assertion(bool condition, const std::string_view msg, const std::string_view file, const int line) {
		if (condition) ; else {
			nova_bark_fatal("{}@{}\nAssertion: {}", file, line, msg);
		}
	}
	#endif // nova_assert

}
