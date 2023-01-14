#pragma once
#include "head.h"

namespace Nova::meta {

	using TypeID = const void* const;

	namespace __I {
		template<typename T>
		struct type {
			static inline constexpr const T* const id = nullptr;
		};

		template<typename T>
		consteval TypeID type_get() {
			return static_cast<TypeID>(&type<T>::id);
		}
	}

	template<typename T>
	consteval TypeID typeID() noexcept {
		return __I::type_get<T>();
	}

}

#define nova_meta_typeid(T) []() { constexpr auto id = ::Nova::meta::typeID<T>(); return id; }()
