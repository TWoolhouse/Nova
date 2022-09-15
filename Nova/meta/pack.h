#pragma once
#include "head.h"
#include "concept.h"
#include "align.h"

namespace Nova::meta {

	template<typename ...Ts>
	struct pack;

	namespace __I {
		// Unable to use the concept contraint as the struct hasn't been defined yet :(
		template<typename Pack> 
		concept is_pack = requires {
			// Should be enough to distinguish a pack from most other types
			typename Pack::tuple;
			{ Pack::count } -> std::convertible_to<size_t>;
			{ Pack::size } -> std::convertible_to<size_t>;
		};

	} // namespace __I

	template<typename ...Ts>
	struct pack {
	public:
		constexpr pack() {}

		using tuple = std::tuple<Ts...>;
		constexpr pack(std::tuple<Ts...>) {}

		// Number of types in the pack
		static constexpr auto count = sizeof...(Ts);
		// Total size of all types
		static constexpr auto size = []() consteval -> size_t {
			if constexpr (count)
				return (sizeof(Ts) + ...);
			else return 0;
		}();
		template<size_t I>
		// Get the Ith type of the pack
		using get = typename std::tuple_element<I, tuple>::type;

		// Null index if the type is not found in the pack
		static constexpr size_t index_null = std::numeric_limits<size_t>::max();
	protected:
		template<size_t I, typename T, typename T0, typename ...Ts>
		static consteval size_t _index() {
			if constexpr (std::same_as<T, T0>) {
				return I;
			}
			if constexpr (!sizeof...(Ts)) {
				return index_null;
			} else {
				return _index<I + 1, T, Ts...>();
			}
		}

	public:
		template<typename T>
		// Get the index of the first matching type.
		static consteval size_t index() { return _index<0, T, Ts...>(); }

	public:
		template<typename ...T>
		// Append types to the pack
		using append = pack<Ts..., T...>;

	protected:
		template<typename ...Ts>
		friend struct pack;
		template<typename Pack, typename ...Packs, typename ...Ts>
		static consteval auto _concat(pack<Ts...>) {
			if constexpr (sizeof...(Packs))
				return decltype(append<Ts...>::template _concat<Packs...>(typename pack<Packs...>::template get<0>{})){};
			else
				return append<Ts...>{};
		}
	public:
		// TODO: Concat constraint
		template<typename ...Packs> // requires is::all_require<nova_meta_concept(__I::is_pack), Packs...>
		// Concatenate packs togeather.
		using concat = decltype(_concat<Packs...>(typename pack<Packs...>::template get<0>{}));

	protected:
		template<size_t I, size_t ...Is>
		static consteval pack<get<I + Is>...> _subpack(std::index_sequence<Is...>) {}
	public:
		template<size_t begin, size_t end = count>
		// A subrange of the pack
		using subpack = decltype(_subpack<begin>(std::make_index_sequence<end - begin>{}));

	protected:
		template<__I::is_pack Element>
		static consteval auto _flattern_elem() { return Element::flat(); }
		template<typename Element>
		static consteval auto _flattern_elem() { return pack<Element>{}; }

		template<size_t ...Is>
		static consteval auto _flattern_n(std::index_sequence<Is...>) {
			return typename pack<>::template concat<decltype(_flattern_elem<get<Is>>())...>{};
		};

		template<uint8_t> requires (count == 0)
		static consteval auto _flattern() -> pack;
		template<uint8_t> requires (count == 1) && (!__I::is_pack<get<0>>)
		static consteval auto _flattern() -> pack;
		template<uint8_t> requires (count == 1) && __I::is_pack<get<0>>
		static consteval auto _flattern() { return decltype(get<0>{})::flat(); }
		template<uint8_t>
		static consteval auto _flattern() { return _flattern_n(std::make_index_sequence<count>{}); };
	public:
		// A flatterned version of the pack
		static consteval auto flat() { return _flattern<0>(); }

	public:
		template<auto Concept>
		// Check if every type of the pack matches the concept
		static consteval auto is() { return nova_meta_concept_exec(Concept, Ts...); }

	public:
		// Highest alignment requirement of every type in the pack
		static constexpr auto alignment = []() consteval -> size_t {
			if constexpr (count == 0) return 0;
			else return std::max({ alignof(Ts)... });
		}();

	protected:
		static consteval size_t _size_align_first(size_t pos) { return align_to(pos, alignof(get<0>)) + sizeof(get<0>); }
		static consteval size_t _size_align(size_t pos) {
			if constexpr (count > 1)
				return subpack<1>::_size_align(_size_align_first(pos));
			else
				return _size_align_first(pos);
		}
		static consteval size_t _size_align() {
			if constexpr (count == 0) return 0;
			else return _size_align(0);
		}
	public:
		// Total size of all types + alignments
		static constexpr auto size_align = []() consteval {
			if constexpr (count == 0) return 0;
			else return align_to(_size_align(), alignment);
		}();

	};

	namespace is {
		template<typename Pack>
		concept pack = requires {
			[]<typename ...Ts>(meta::pack<Ts...>) consteval {}(Pack{});
		};
	} // namespace is

}