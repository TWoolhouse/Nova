#pragma once
#include "npch.h"

namespace Nova::input {

	using MousePos = std::pair<unsigned int, unsigned int>;

	enum class Mouse : uint8_t {
		NONE = 0,
		Left, Right, Middle, VB1, VB2,

		COUNT
	};

}

formatter_enum(Nova::input::Mouse, uint8_t);
