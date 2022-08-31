#pragma once
#include "meta/head.h"
#include "bark/bark.h"
#include "_vulkan.h"

namespace Nova::abyss::def {
constexpr auto debug =
#ifndef NOVA_ABYSS_DEBUG
#ifdef NOVA_DEBUG
#define NOVA_ABYSS_DEBUG
true;
#else // !NOVA_DEBUG
false;
#endif // NOVA_DEBUG
#else // !NOVA_ABYSS_DEBUG
#undef NOVA_ABYSS_DEBUG
false;
#endif // !__N_OVA_ABYSS_DEBUG
}

#ifdef NOVA_DEBUG
#define NVK_CHECK(expr, msg) ([&]() { \
	auto __n_vk_check_result = expr; \
	nova_assert(__n_vk_check_result, msg " : " #expr); \
	return __n_vk_check_result; \
})()
#else // !NOVA_DEBUG
#define NVK_CHECK(expr, msg) expr
#endif // NOVA_DEBUG

nova_meta_enum_str(vk::Result, result);

namespace Nova::abyss::nvk {
	template<typename T, typename VK>
	// Extends a class through CRTP to have a conversion to its underlying type
	struct OPVK {

		inline constexpr operator const VK&() {
			static_assert(std::same_as<decltype(T::self), VK>, "T::self is not the same as the VK type!");
			return static_cast<T*>(this)->self;
		}
		inline constexpr operator const VK&() const {
			static_assert(std::same_as<decltype(T::self), VK>, "T::self is not the same as the VK type!");
			return static_cast<const T*>(this)->self;
		}

		inline constexpr operator typename VK::CType() {
			return operator const VK &();
		}
		inline constexpr operator const typename VK::CType() const {
			return operator const VK &();
		}

	};
}
