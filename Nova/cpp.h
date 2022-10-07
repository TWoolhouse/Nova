#pragma once
// Features comming in future versions of C++
#include <type_traits>

namespace cpp {

	template<class Enum>
	constexpr std::underlying_type_t<Enum> to_underlying(Enum e) noexcept {
		return static_cast<std::underlying_type_t<Enum>>(e);
	}

}