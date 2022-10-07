#pragma once
#include "defines.h"

#define __C_ONCAT(x, y) x##y
#define CONCAT(x, y) __C_ONCAT(x, y)

#define __S_TRINGIFY(x) #x
#define STRINGIFY(x) __S_TRINGIFY(x)

#define formatter_enum(EnumName) \
template<class CharT> \
struct std::formatter<EnumName, CharT> : std::formatter<std::underlying_type_t<EnumName>, CharT> { \
	template<class FormatContext> \
	auto format(EnumName _enum, FormatContext& fc) { \
		return std::formatter<std::underlying_type_t<EnumName>, CharT>::format(cpp::to_underlying(_enum), fc); \
	} \
}

#ifdef NOVA_DEBUG
#define nova_debug_exc(expr) expr
#else // !NOVA_DEBUG
#define nova_debug_exc(expr)
#endif // NOVA_DEBUG
