#pragma once
#include "head.h"
#include "pack.h"

namespace Nova::meta {

	template<typename T, auto v, typename V = decltype(v)>
	struct TVPair {
		using key = T;
		using value_type = V;
		static constexpr value_type value = v;
	};

	namespace __I {
		template<typename T>
		concept TVPair = requires {
			typename T::key;
			typename T::value_type;
			{ T::value } -> std::convertible_to<const typename T::value_type>;
		};
	} // namespace __I

	template<typename ...Ts> requires (__I::TVPair<Ts> && ...)
	struct TVMap {
		using pack = meta::pack<Ts...>;
		using keys = meta::pack<typename Ts::key...>;
		using values = meta::pack<typename Ts::value_type...>;
		template<typename T>
		NODISCARD static consteval auto get() {
			constexpr auto index = keys::template index<T>();
			static_assert(index != keys::index_null, "Type is not in TVMap");
			return pack::get<index>::value;
		}

		template<typename T>
		using get_value_type = values::template get<keys::template index<T>()>;
	};

} // namespace Nova::meta