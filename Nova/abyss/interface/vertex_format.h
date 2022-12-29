#pragma once
#include "meta/head.h"
#include "meta/pack.h"
#include "meta/map/tv.h"
#include "meta/concept.h"

namespace Nova::abyss::buffer::interface {

	template<typename ...Pairs>
	struct Format {
	protected:
		using Map = meta::map::TV<Pairs...>;
		static_assert(Map::value_types::template is<nova_meta_concept(meta::is::all_same)>(), "All Pairs must have the same value type");
	protected:
		template<typename T>
		static consteval T get_types() { return {}; }
		template<typename ...Ts>
		static consteval auto get_types(meta::pack<Ts...>) { return meta::pack<meta::pack<decltype(get_types<Ts>())>...>::flat(); }
		template<meta::is::pack Pack>
		static consteval auto get_types() { return get_types(Pack{}); }
		template<typename T> requires requires { T::Spec; }
		static consteval auto get_types() { return get_types<typename T::Spec>(); }

		template<typename ...Ts>
		static consteval auto convert(meta::pack<Ts...>) {
			return std::make_tuple(Map::template get<Ts>()...);
		}

	public:
		template<typename T>
		using types = decltype(get_types<T>().flat());

		template<typename T> requires meta::is::pack<T> && (!requires { typename T::Spec; })
		// Get an array of mappings
		static consteval auto get() {
			using Pack = types<T>;
			return meta::tuple::as_array(convert(Pack{}));
		}

		template<typename T>
		// Get a direct type mapping
		static consteval auto get() {
			return Map::template get<T>();
		}

		template<typename T> requires requires { typename T::Spec; }
		static consteval auto get() = delete;
	};

}