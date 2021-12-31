#include "npch.h"
#include "log.h"

#include "colours.h"
#include <iostream>

#ifdef nova_assert
#include <intrin.h>
#endif // nova_assert

namespace Nova::bark {

	void Initialize() {
		nova_bark_init("[Bark] Done!");
	}
	void Terminate() {
		nova_bark_term("[Bark] ...");
		std::cout << Colour::Default; std::cerr << Colour::Default;
	}

	void submit(const Level level, const std::string& msg) {
		static constexpr std::pair<std::string_view, Colour> levels[static_cast<char>(Level::MAX)] = {
			{"Debug", Colour::Green},
			{"Trace", Colour::Cyan},
			{"Info", Colour::White},
			{"Init", Colour::Blue},
			{"Term", Colour::Magenta},
			{"Warn", Colour::Yellow},
			{"Error", Colour::Red},
			{"Fatal", Colour::BRed},
		};
		const auto& lvl = levels[static_cast<char>(level)];
		(level < Level::Error ? std::cout : std::cerr) << lvl.second << "[" << lvl.first << "] " << msg << std::endl;
	}

	#ifdef nova_assert
	void assertion(bool condition, const std::string_view msg, const std::string_view file, const int line) {
		if (condition) ; else {
			nova_bark_fatal("{}@{}\nAssertion: {}", file, line, msg);
		}
	}
	#endif // nova_assert

}
