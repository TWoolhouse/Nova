#pragma once
#include "head.h"
#include "concept.h"
#include "pack.h"

namespace Nova::meta {

	template<auto... Concepts>
	struct lace { static constexpr auto size = sizeof...(Concepts); };

	namespace __I {
		template<auto F, std::size_t I, std::size_t Step, meta::is::pack Pack>
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

	namespace is {
		template<typename Concepts, typename... Ts>
		concept interlace = __I::interlace(Concepts{}, meta::pack<Ts...>{}, std::make_index_sequence<Concepts::size>{}) && requires {
			[]<auto... Fs>(lace<Fs...>){}(Concepts{});
		} && !(sizeof...(Ts) % Concepts::size);
	} // namespace is

} // namespace Nova::meta
