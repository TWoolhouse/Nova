#pragma once
#include "meta/head.h"

namespace Nova::nvtl::alloc {

	template<typename T>
	class Default {
	public:
		using value_type = T;
		constexpr Default() = default;
		template<typename U>
		Default(const Default<U>&) noexcept {}

		constexpr T* allocate(const size_t n) const {
			nova_bark_debug("Allocate {}", n);
			return reinterpret_cast<T*>(operator new(n * sizeof(T)));
		}
		constexpr void deallocate(T* const ptr, size_t n) const noexcept {
			nova_bark_debug("Deallocate {}", n);
			return operator delete(ptr, n);
		}

		constexpr bool operator==(const Default& other) const noexcept { return true; }
	};

}