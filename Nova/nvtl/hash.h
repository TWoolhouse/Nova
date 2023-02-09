#pragma once
#include "meta/head.h"

namespace Nova::nvtl {

	template<typename T>
	constexpr std::size_t hash(T&& object) {
		return std::hash<std::remove_cvref_t<T>>{}(std::forward<T>(object));
	}

	// https://www.boost.org/doc/libs/1_55_0/doc/html/hash/combine.html
	constexpr std::size_t hash_combine(size_t lhs, size_t rhs) noexcept {
		if constexpr (sizeof(size_t) >= 8) {
			lhs ^= rhs + 0x517cc1b727220a95 + (lhs << 6) + (lhs >> 2);
		}
		else {
			lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
		}
		return lhs;
	}

	namespace __I {
		template<typename T, typename ...Args>
		constexpr auto hash_all(std::size_t hash, T&& arg, Args&& ...args) {
			if constexpr (sizeof...(Args) <= 0) {
				return nvtl::hash_combine(hash, nvtl::hash(std::forward<T>(arg)));
			} else {
				return hash_all(nvtl::hash_combine(hash, nvtl::hash(std::forward<T>(arg))), std::forward<Args>(args)...);
			}
		}
	} // namespace __I

	template<typename ...Args> requires (sizeof...(Args) > 0)
	constexpr std::size_t hash_all(Args&& ...args) {
		return __I::hash_all(0, std::forward<Args>(args)...);
	}

} // namespace Nova::nvtl
