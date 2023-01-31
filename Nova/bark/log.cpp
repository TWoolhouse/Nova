#include "npch.h"
#include "log.h"

#include "colours.h"
#include "location_str.h"

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



	void submit(const Level level, const Location& location, const std::string& msg) {
		static constexpr std::pair<std::string_view, std::pair<Colour, Colour>> levels[static_cast<char>(Level::MAX)] = {
			{"Fatal",	{Colour::Black,		Colour::BRed}},
			{"Error",	{Colour::White,		Colour::BRed}},
			{"Warn",	{Colour::Yellow,	Colour::BDefault}},
			{"Todo",	{Colour::Black,		Colour::BYellow}},
			{"Info",	{Colour::White,		Colour::BDefault}},
			{"Init",	{Colour::Blue,		Colour::BDefault}},
			{"Term",	{Colour::Magenta,	Colour::BDefault}},
			{"Trace",	{Colour::Cyan,		Colour::BDefault}},
			{"Debug",	{Colour::Green,		Colour::BDefault}},
			{"Temp",	{Colour::Black,		Colour::BWhite}},
		};
		auto&& [name, colour] = levels[static_cast<char>(level)];
		#ifdef __N_OVA_BARK_CONSOLE
			(level < Level::Error ? std::cout : std::cerr) << // Stream
				colour.first << colour.second << // Colours
				"[" << name << "] " << msg << std::endl; // Message
		#endif // __N_OVA_BARK_CONSOLE
		#ifdef __N_OVA_BARK_FILE
			log_file << // Stream
				nova_bark_format("{: <80}\t{}", nova_bark_format("[{}] {}", name, msg), location_string(location)) << std::endl;
		#endif // __N_OVA_BARK_FILE
	}

}
