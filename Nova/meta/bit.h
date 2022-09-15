#pragma once
#include "head.h"

namespace Nova::meta {

	NODISCARD constexpr uintmax_t bit(uint8_t pos) {
		if (pos == 0)	return 0;
		return (static_cast<uintmax_t>(1) << (pos - 1));
	}

} // namespace Nova::meta
