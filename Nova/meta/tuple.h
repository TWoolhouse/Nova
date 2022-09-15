#pragma once
#include "head.h"
#include "concept.h"

namespace Nova::meta::tuple {

	template<typename T>
	NODISCARD constexpr auto flattern(T&& tuple);
	template<typename T>
	NODISCARD constexpr auto flattern(T&& obj, char) {
		if constexpr (is::specialisation_of<std::remove_cvref_t<T>, std::tuple>) {
			return flattern(std::forward<T>(obj));
		} else {
			return std::make_tuple(std::forward<T>(obj));
		}
	}
	template<typename T, size_t ...Is>
	NODISCARD constexpr auto flattern(T&& tuple, std::index_sequence<Is...>) {
		return std::tuple_cat(flattern(std::get<Is>(std::forward<T>(tuple)), char{})...);
	}

	template<typename T>
	NODISCARD constexpr auto flattern(T&& tuple) {
		return flattern(std::forward<T>(tuple), std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<T>>>{});
	}



	template<typename F, typename Tuple>
	constexpr auto for_each(F&& func, Tuple&& tuple) {
		return std::apply([&](auto ...x){(..., func(x));} , tuple);
	}



	// https://stackoverflow.com/a/54487034/13268833
	template<typename Tuple>
	NODISCARD constexpr auto as_array(Tuple&& tuple) {
		return std::apply(
			[](auto&& ...elm){ return std::array{std::forward<decltype(elm)>(elm)...}; },
			tuple
		);
	}

}