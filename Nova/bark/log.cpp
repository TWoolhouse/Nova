#include "npch.h"
#include "log.h"

#include "colours.h"
#include <iostream>

namespace Nova::bark {

	void Initialize() {
		nova_bark_init("[Bark] Done!");
	}
	void Terminate() {
		nova_bark_term("[Bark] ...");
		std::cout << Colour::Default; std::cerr << Colour::Default;
	}

	void submit(const Level level, const std::string& msg) {
		static constexpr std::pair<std::string_view, std::pair<Colour, Colour>> levels[static_cast<char>(Level::MAX)] = {
			{"Debug",	{Colour::Green,	Colour::BDefault}},
			{"Trace",	{Colour::Cyan,	Colour::BDefault}},
			{"Info",	{Colour::White,	Colour::BDefault}},
			{"Init",	{Colour::Blue,	Colour::BDefault}},
			{"Term",	{Colour::Magenta,	Colour::BDefault}},
			{"Warn",	{Colour::Yellow,	Colour::BDefault}},
			{"Error",	{Colour::Red,		Colour::BDefault}},
			{"Fatal",	{Colour::Black,	Colour::BRed}},
		};
		const auto& lvl = levels[static_cast<char>(level)];
		(level < Level::Error ? std::cout : std::cerr) << // Stream
			lvl.second.first << lvl.second.second << // Colours
			"[" << lvl.first << "] " << msg << std::endl; // Message
	}

#ifdef nova_assert
	void assertion(bool condition, const std::string_view msg, const std::string_view file, const int line) {
		if (condition) [[likely]]; else {
			nova_bark_fatal("{}@{}\nAssertion: {}", file, line, msg);
		}
	}
#endif // nova_assert

}
