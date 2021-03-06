#pragma once
#include "lib.h"
#include "aliases.h"

template<typename T> requires(!requires (T o) {
	std::format("{}"sv, o);
})
std::ostream& operator<<(std::ostream& stream, const T& obj) {
	return stream << std::format("{}"sv, obj);
}

template<typename E> requires std::is_enum_v<E>
inline NODISCARD constexpr E operator&(const E a, const E b) noexcept {
	return static_cast<E>(static_cast<std::underlying_type_t<E>>(a) & static_cast<std::underlying_type_t<E>>(b));
}
template<typename E> requires std::is_enum_v<E>
inline NODISCARD constexpr E operator|(const E a, const E b) noexcept {
	return static_cast<E>(static_cast<std::underlying_type_t<E>>(a) | static_cast<std::underlying_type_t<E>>(b));
}
template<typename E> requires std::is_enum_v<E>
inline NODISCARD constexpr E operator^(const E a, const E b) noexcept {
	return static_cast<E>(static_cast<std::underlying_type_t<E>>(a) ^ static_cast<std::underlying_type_t<E>>(b));
}
template<typename E> requires std::is_enum_v<E>
inline NODISCARD constexpr E operator~(const E a) noexcept {
	return static_cast<E>(~static_cast<std::underlying_type_t<E>>(a));
}
