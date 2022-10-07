#pragma once
#include "lib.h"
#include "aliases.h"

namespace Nova::meta {

	template<typename Enum> requires std::is_enum_v<Enum>
	std::string_view estr(Enum arg) = delete;
	#define nova_meta_enum_str(Enum, arg) template<> std::string_view Nova::meta::estr<>(Enum arg)

} // namespace Nova::meta

template<typename Enum, class CharT> requires std::is_enum_v<Enum> && requires (Enum e) {
	Nova::meta::estr(e);
}
struct std::formatter<Enum, CharT> : public std::formatter<std::string_view, CharT> {
	template<class FormatContext>
	auto format(Enum arg, FormatContext& fc) {
		return formatter<std::string_view, CharT>::format(Nova::meta::estr(arg), fc);
	}
};

template<typename Enum, class CharT> requires std::is_enum_v<Enum> && (!requires (Enum e) {
	Nova::meta::estr(e);
})
struct std::formatter<Enum, CharT> : public std::formatter<std::underlying_type_t<Enum>, CharT> {
	template<class FormatContext>
	auto format(Enum arg, FormatContext& fc) {
		return formatter<std::underlying_type_t<Enum>, CharT>::format(cpp::to_underlying(arg), fc);
	}
};
