#pragma once
#include "meta/head.h"

namespace Nova::nvtl {

	template<typename T>
	size_t hash(const T& object) noexcept {
		return std::hash<T>{}(object);
	}

	// https://www.boost.org/doc/libs/1_55_0/doc/html/hash/combine.html
	size_t hash_combine(size_t lhs, size_t rhs) {
		if constexpr (sizeof(size_t) >= 8) {
			lhs ^= rhs + 0x517cc1b727220a95 + (lhs << 6) + (lhs >> 2);
		}
		else {
			lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
		}
		return lhs;
	}

} // namespace Nova::nvtl
