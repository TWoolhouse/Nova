#pragma once
#include <iosfwd>

namespace Nova::bark {

	enum class Colour {
		Default = 0,
		Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, FDefault,
		BBlack, BRed, BGreen, BYellow, BBlue, BMagenta, BCyan, BWhite, BDefault,

		FBlack = Black,
		FRed = Red,
		FGreen = Green,
		FYellow = Yellow,
		FBlue = Blue,
		FMagenta = Magenta,
		FCyan = Cyan,
		FWhite = White,
	};

}

std::ostream& operator<<(std::ostream&, const Nova::bark::Colour colour);
