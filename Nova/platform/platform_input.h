#pragma once
#include "input/key.h"
#include "input/mouse.h"

namespace Nova::plat::input {

	constexpr Nova::input::Key key(const unsigned int code);
	constexpr Nova::input::Mouse mouse(const unsigned int code);

}