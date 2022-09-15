#pragma once
#include "head.h"

namespace Nova::meta::smallest {

	template<size_t N>
	using uint = std::conditional_t < N <= std::numeric_limits<uint8_t>::max(), uint8_t,
		std::conditional_t < N <= std::numeric_limits<uint16_t>::max(), uint16_t,
		std::conditional_t< N <= std::numeric_limits<uint32_t>::max(), uint32_t,
		std::conditional_t< N <= std::numeric_limits<uint64_t>::max(), uint64_t,
		uintmax_t
	>>>>;

} // namespace Nova::meta::smallest