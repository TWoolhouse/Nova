#pragma once
#include "head.h"

namespace Nova::meta {

	template<typename ...Ts>
	concept all_same = sizeof...(Ts) < 2 ||
		(std::same_as<std::tuple_element_t<0, std::tuple<Ts...>>, Ts> && ...);

	template<typename T, typename ...Ts>
	concept all_convertable = sizeof...(Ts) < 1 ||
		(std::convertible_to<Ts, T> && ...);

}
