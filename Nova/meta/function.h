#pragma once
#include "head.h"

namespace Nova::meta {

	template<typename ...Ts>
	struct pack {
		static constexpr auto size = sizeof...(Ts);
		using tuple = std::tuple<Ts...>;
		template<size_t I>
		using get = typename std::tuple_element<I, tuple>::type;
	};

	template<typename P>
	concept Pack = requires (P p) {
		[]<typename ...Ts>(pack<Ts...>) {}(P{});
	};

	template<typename T, typename ...Ts>
	constexpr pack<Ts..., T> packer(pack<Ts...>);

	template<typename ...Ts>
	struct decay : public pack<std::decay_t<Ts> ...> {};

	template<typename Sig> struct signature;
	template<typename R, typename ...Args> struct signature<R(Args...)> : public pack<Args...> {
		using decay = meta::decay<Args...>;
		using ret = R;
	};

	template<typename T, typename  ...Ts>
	constexpr size_t sizes() {
		if constexpr (sizeof...(Ts) > 0) {
			return sizeof(T) + sizes<Ts...>();
		} return sizeof(T);
	}

	namespace __I {
		template<size_t I, typename T, typename T0, typename ...Ts>
		constexpr size_t type_index() {
			if constexpr (std::is_same_v<T, T0>) {
				return I;
			}
			if constexpr (!sizeof...(Ts)) {
				return std::numeric_limits<size_t>::max();
			}
			else {
				return type_index<I + 1, T, Ts...>();
			}
		}
	} // namespace __I

	template<typename T, typename ...Ts>
	constexpr size_t type_index() {
		if constexpr (!sizeof...(Ts)) {
			return std::numeric_limits<size_t>::max();
		}
		return __I::type_index<0, T, Ts...>();
	}
	template<typename T, typename ...Ts>
	constexpr size_t type_index(pack<Ts...>) {
		if constexpr (!sizeof...(Ts)) {
			return std::numeric_limits<size_t>::max();
		}
		return __I::type_index<0, T, Ts...>();
	}
	constexpr auto type_index_null = std::numeric_limits<size_t>::max();

	template<size_t I, typename ...Ts>
	using type_get = typename std::tuple_element<I, std::tuple<Ts...>>::type;

	namespace __I {
		template<std::size_t N, typename... T, std::size_t... I>
		pack<std::tuple_element_t<N + I, std::tuple<T...>>...>
			constexpr sub(std::index_sequence<I...>);
	} // namespace __I

	template<size_t I, size_t S, typename ...Ts>
	struct subpack {
		using type = typename decltype(__I::sub<I, Ts...>(std::make_index_sequence<std::min(sizeof...(Ts) - I, S)>{}));
	};

	template<size_t I, size_t S, typename ...Ts>
	constexpr subpack<I, S, Ts...>::type subpack_pack(pack<Ts...>);

	template<typename T = std::size_t>
	inline constexpr auto max() { return std::numeric_limits<T>::max(); }

} // namespace Nova::meta
