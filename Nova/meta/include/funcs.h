#pragma once
#include "lib.h"
#include "aliases.h"
#include "defines.h"

template<typename T> requires(!requires (T o) {
	std::format("{}"sv, o);
})
std::ostream& operator<<(std::ostream& stream, const T& obj) {
	return stream << std::format("{}"sv, obj);
}

template<typename E> requires std::is_enum_v<E>
NODISCARD inline constexpr E operator&(const E a, const E b) noexcept {
	return static_cast<E>(cpp::to_underlying(a) & cpp::to_underlying(b));
}
template<typename E> requires std::is_enum_v<E>
NODISCARD inline constexpr E operator|(const E a, const E b) noexcept {
	return static_cast<E>(cpp::to_underlying(a) | cpp::to_underlying(b));
}
template<typename E> requires std::is_enum_v<E>
NODISCARD inline constexpr E operator^(const E a, const E b) noexcept {
	return static_cast<E>(cpp::to_underlying(a) ^ cpp::to_underlying(b));
}
template<typename E> requires std::is_enum_v<E>
NODISCARD inline constexpr E operator~(const E a) noexcept {
	return static_cast<E>(~cpp::to_underlying(a));
}

template<typename E> requires std::is_enum_v<E>
inline constexpr E& operator&=(E& a, const E b) noexcept {
	a = a & b;
	return a;
}
template<typename E> requires std::is_enum_v<E>
inline constexpr E& operator|=(E& a, const E b) noexcept {
	a = a | b;
	return a;
}
template<typename E> requires std::is_enum_v<E>
inline constexpr E& operator^=(E& a, const E b) noexcept {
	a = a ^ b;
	return a;
}
