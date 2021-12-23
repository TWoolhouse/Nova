#pragma once
#include "defines.h"

namespace Nova::meta {

	template<typename ...Ts>
	struct pack {
		using tuple = std::tuple<Ts...>;
	};

	template<typename T, typename ...Ts>
	pack<Ts..., T> packer(pack<Ts...>);

	template<typename ...Ts>
	struct decay : public pack<std::decay_t<Ts> ...> {};

	template<typename Sig> struct signature;
	template<typename R, typename ...Args> struct signature<R(Args...)> : public pack<Args...> {
		using decay = meta::decay<Args...>;
		using ret = R;
	};

}