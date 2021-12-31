#include "npch.h"
#include "colours.h"
#include <iostream>

constexpr uint8_t colour_code(const Nova::bark::Colour colour) {
	using Nova::bark::Colour;
	switch (colour) {
	case (Colour::Default):	return 0;
	case (Colour::Black):	return 30;
	case (Colour::Red):	return 31;
	case (Colour::Green):	return 32;
	case (Colour::Yellow):	return 33;
	case (Colour::Blue):	return 34;
	case (Colour::Magenta):	return 35;
	case (Colour::Cyan):	return 36;
	case (Colour::White):	return 37;
	case (Colour::FDefault):	return 39;
	case (Colour::BBlack):	return 40;
	case (Colour::BRed):	return 41;
	case (Colour::BGreen):	return 42;
	case (Colour::BYellow):	return 43;
	case (Colour::BBlue):	return 44;
	case (Colour::BMagenta):	return 45;
	case (Colour::BCyan):	return 46;
	case (Colour::BWhite):	return 47;
	case (Colour::BDefault):	return 49;
	default:
		return 0;
	}

}

std::ostream& operator<<(std::ostream& stream, const Nova::bark::Colour colour) {
	return stream << std::format("\x1b[{}m", std::to_string(colour_code(colour))).c_str();
}