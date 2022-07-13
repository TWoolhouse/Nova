#pragma once
#include "head.h"
#include "function.h"

namespace Nova::meta {

	template<typename ...Ts>
	concept all_same = sizeof...(Ts) < 2 ||
		(std::same_as<std::tuple_element_t<0, std::tuple<Ts...>>, Ts> && ...);

	template<typename T, typename ...Ts>
	concept all_convertable = sizeof...(Ts) < 1 ||
		(std::convertible_to<Ts, T> && ...);

	template<auto... Concepts>
	struct lace { static constexpr auto size = sizeof...(Concepts); };

	namespace __I {
#define nova_meta_concept(Concept) \
	[]<typename... Ts>() consteval { return Concept<Ts...>; }
#define nova_meta_concept_exec(ConceptLambda, ...) ConceptLambda.template operator()<__VA_ARGS__>()

		template<auto F, std::size_t I, std::size_t Step, meta::Pack Pack>
		constexpr auto interlace_thread() {
			if constexpr (I >= Pack::size) return true;
			else
				return (nova_meta_concept_exec(F, typename Pack::template get<I>)) && (interlace_thread<F, I + Step, Step, Pack>());
		};

		template<auto... Fs, typename... Ts, std::size_t... Is>
		constexpr auto interlace(lace<Fs...> concepts, pack<Ts...> types, std::index_sequence<Is...>) {
			return (interlace_thread<Fs, Is, sizeof...(Fs), decltype(types)>() && ...);
		}

	} // namespace __I

	template<typename Concepts, typename... Ts>
	concept interlace = __I::interlace(Concepts{}, meta::pack<Ts...>{}, std::make_index_sequence<Concepts::size>{}) && requires {
		[]<auto... Fs>(lace<Fs...>){}(Concepts{});
	} && !(sizeof...(Ts) % Concepts::size);

} // namespace Nova::meta
