#pragma once
#include "head.h"
#include "concept.h"
#include "align.h"
#include "pack.h"

namespace Nova::meta {

	template<auto ...Vs>
	struct vpack;

	namespace __I {
		// Unable to use the concept contraint as the struct hasn't been defined yet :(
		template<typename Pack>
		concept is_vpack = requires {
			typename Pack::pack;
			requires is_pack<typename Pack::pack>;
			{ Pack::count } -> std::convertible_to<size_t>;
		};

	} // namespace __I

	template<auto ...Vs>
	struct vpack {
	public:
		constexpr vpack() {}
		using pack = meta::pack<decltype(Vs)...>;

		// Number of values in the pack
		static constexpr auto count = sizeof...(Vs);

	protected:
		template<auto V0, auto ...Vs>
		static consteval auto _get_first() { return V0; }

		template<auto V0, auto ...Vs>
		using _shift = vpack<Vs...>;

		template<size_t I> requires (validate<I>())
		static consteval auto _get() {
			if constexpr (I == 0) {
				return _get_first<Vs...>();
			}
			else {
				return _shift<Vs...>::template get<I - 1>();
			}
		}

		template<size_t I>
		static consteval bool validate() {
			constexpr auto expr = I < count;
			static_assert(expr, "VPack Index is greater than the VPack count");
			return expr;
		}

	public:
		// Get the Ith value of the pack
		template<size_t I>
		NODISCARD static consteval auto get() { return _get<I>(); }

		// Null index if the value is not found in the pack
		static constexpr size_t index_null = std::numeric_limits<size_t>::max();
	protected:
		template<size_t I, auto V, auto V0, auto ...Vs>
		static consteval size_t _index() {
			if constexpr (V == V0) {
				return I;
			}
			if constexpr (!sizeof...(Vs)) {
				return index_null;
			}
			else {
				return _index<I + 1, V, Vs...>();
			}
		}

	public:
		template<auto V>
		// Get the index of the first matching value.
		NODISCARD static consteval size_t index() { return _index<0, V, Vs...>(); }

	public:
		template<auto ...V>
		// Append values to the pack
		using append = vpack<Vs..., V...>;

	protected:
		template<size_t I, size_t ...Is>
		static consteval vpack<get<I + Is>()...> _subpack(std::index_sequence<Is...>) {}
	public:
		template<size_t begin, size_t end = count>
		// A subrange of the pack
		using subpack = decltype(_subpack<begin>(std::make_index_sequence<end - begin>{}));

	public:
		template<auto Concept>
		// Check if every type of the pack matches the concept
		NODISCARD static consteval auto is() { return nova_meta_concept_exec(Concept, Vs...); }

	};

	namespace is {
		template<typename Pack>
		concept vpack = requires {
			[] <auto ...Vs>(meta::vpack<Vs...>) consteval {}(Pack{});
		};
	} // namespace is

}