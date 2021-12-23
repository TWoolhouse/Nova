#pragma once
#include "npch.h"

namespace Nova::input {

	using MousePos = std::pair<unsigned int, unsigned int>;

	enum class Mouse : uint8_t {
		Left, Right, Middle, Num4, Num5, COUNT
	};

}