#pragma once
#include "meta/head.h"

#if defined(NOVA_MLB_NOVA)
#elif defined(NOVA_MLB_GLM)
#include "_glm.h"
#endif // NOVA_MLB_API

namespace Nova::mlb {

	template<typename T>
	inline NODISCARD constexpr T clamp(T v, T mn, T mx) noexcept { return std::max(mn, std::min(mx, v)); }

}