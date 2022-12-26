#pragma once
#include "lib.h"
#include "aliases.h"
#include "../bit.h"
#include "../string.h"

namespace Nova::meta {

	template<typename Enum> requires std::is_enum_v<Enum>
	std::string_view estr(Enum arg) = delete;
	#define nova_meta_enum_str(Enum, arg) template<> std::string_view Nova::meta::estr<>(Enum arg)

	template<typename Enum> requires std::is_enum_v<Enum>
	auto ebits(Enum arg) {
		constexpr auto bits = sizeof(Enum) * 8;
		std::bitset<bits> bitset(cpp::to_underlying(arg));
		auto iterator = std::views::iota(static_cast<decltype(bits)>(0), bits);
		return iterator 
			| std::views::filter([bitset](auto&& index) { return bitset.test(index); }) 
			| std::views::transform([bitset](auto&& index) { return static_cast<Enum>(meta::bit(index + 1)); });
	}

	template<typename Enum>
	std::string estrs(Enum arg) {
		return meta::str::join(meta::ebits(arg) | std::views::transform([](auto&& e) { return meta::estr(e); }));
	}

	// Checks if a flag is set in an enum
	template<typename Enum> requires std::is_enum_v<Enum>
	inline constexpr bool etest(Enum bitset, Enum flag) { return cpp::to_underlying(bitset & flag); }

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
