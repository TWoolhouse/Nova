#pragma once
#include "lib.h"
#include "aliases.h"
#include "defines.h"
#include "../bit.h"
#include "../string.h"
#include "../concept.h"

namespace Nova::meta::enm {

	template<typename Enum> requires std::is_enum_v<Enum>
	std::string_view str(Enum arg) = delete;
	#define nova_meta_enum_str(Enum, arg) template<> std::string_view Nova::meta::enm::str<>(Enum arg)

	template<typename Enum> requires std::is_enum_v<Enum>
	auto bits(Enum arg) {
		static_assert(sizeof(Enum) * 8 <= meta::bit(sizeof(uint8_t) * 8), "meta::bit only supports uint8_t sized indicies!");
		constexpr auto bits = sizeof(Enum) * 8;
		std::bitset<bits> bitset(cpp::to_underlying(arg));
		auto iterator = std::views::iota(static_cast<decltype(bits)>(0), bits);
		return iterator
			| std::views::filter([bitset](auto&& index) { return bitset.test(index); })
			| std::views::transform([bitset](auto&& index) { return static_cast<Enum>(meta::bit(static_cast<uint8_t>(index + 1))); });
	}

	template<typename Enum>
	std::string strs(Enum arg) {
		return meta::str::join(bits(arg) | std::views::transform([](auto&& e) { return meta::enm::str(e); }));
	}


	// Is the value of the enum not 0
	template<is::Enum Enum>
	inline constexpr bool is(Enum bitset) { return cpp::to_underlying(bitset); }

	// Checks if a flag is set in an enum
	template<typename Enum> requires std::is_enum_v<Enum>
	inline constexpr bool test(Enum bitset, Enum flag) { return is(bitset & flag); }

	template<typename To, is::Enum From> requires is::enum_from<From, To>
	inline constexpr To to(From from) noexcept { return static_cast<To>(from); }

} // namespace Nova::meta::enm

template<typename Enum, class CharT> requires std::is_enum_v<Enum> && requires (Enum e) {
	Nova::meta::enm::str(e);
}
struct std::formatter<Enum, CharT> : public std::formatter<std::string_view, CharT> {
	template<class FormatContext>
	auto format(Enum arg, FormatContext& fc) {
		return formatter<std::string_view, CharT>::format(Nova::meta::enm::str(arg), fc);
	}
};

template<typename Enum, class CharT> requires std::is_enum_v<Enum> && (!requires (Enum e) {
	Nova::meta::enm::str(e);
})
struct std::formatter<Enum, CharT> : public std::formatter<std::underlying_type_t<Enum>, CharT> {
	template<class FormatContext>
	auto format(Enum arg, FormatContext& fc) {
		return formatter<std::underlying_type_t<Enum>, CharT>::format(cpp::to_underlying(arg), fc);
	}
};
