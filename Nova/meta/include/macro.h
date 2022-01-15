#pragma once
#include "defines.h"

template<typename T> requires(!requires (T o) {
	std::format("{}"sv, o);
})
std::ostream& operator<<(std::ostream& stream, const T& obj) {
	return stream << std::format("{}"sv, obj);
}

#define __C_ONCAT(x, y) x##y
#define CONCAT(x, y) __C_ONCAT(x, y)

#define formatter_enum(EnumName) \
template<class CharT> \
struct std::formatter<EnumName, CharT> : std::formatter<std::underlying_type_t<EnumName>, CharT> { \
	template<class FormatContext> \
	auto format(EnumName _enum, FormatContext& fc) { \
		return std::formatter<std::underlying_type_t<EnumName>, CharT>::format(static_cast<std::underlying_type_t<EnumName>>(_enum), fc); \
	} \
}
