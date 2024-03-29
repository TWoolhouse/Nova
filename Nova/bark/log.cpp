#include "npch.h"
#include "log.h"

#include "colours.h"
#include <iostream>
#include <fstream>

namespace Nova::bark {

	#ifdef __N_OVA_BARK_FILE
		inline std::ofstream log_file;
	#endif // __N_OVA_BARK_FILE

	void Initialize() {
		#ifdef __N_OVA_BARK_FILE
			log_file = std::ofstream{ "log.log" };
		#endif // __N_OVA_BARK_FILE
		nova_bark_init("[Bark] Done!");
	}
	void Terminate() {
		nova_bark_term("[Bark] ...");
		#ifdef __N_OVA_BARK_FILE
			log_file.close();
		#endif // __N_OVA_BARK_FILE
		#ifdef __N_OVA_BARK_CONSOLE
			std::cout << Colour::Default; std::cerr << Colour::Default;
		#endif // __N_OVA_BARK_CONSOLE

	}

	void submit(const Level level, const char* location, const std::string& msg) {
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
		auto&& [name, colour] = levels[static_cast<char>(level)];
		#ifdef __N_OVA_BARK_CONSOLE
			(level < Level::Error ? std::cout : std::cerr) << // Stream
				colour.first << colour.second << // Colours
				"[" << name << "] " << msg << std::endl; // Message
		#endif // __N_OVA_BARK_CONSOLE
		#ifdef __N_OVA_BARK_FILE
			log_file << // Stream
				nova_bark_format("{: <80}\t{}", nova_bark_format("[{}] {}", name, msg), location) << std::endl;
		#endif // __N_OVA_BARK_FILE
	}

#ifdef __N_OVA_BARK_ASSERT
	void assertion(bool condition, const std::string_view msg, const std::string_view location) {
		if (condition) [[likely]]; else {
			nova_bark_fatal("{}\nAssertion: {}", location, msg);
		}
	}
#endif // __N_OVA_BARK_ASSERT

}
