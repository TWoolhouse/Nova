#pragma once
#include "meta/head.h"
#include "config.h"

namespace Nova::bark {
	#ifdef __N_OVA_BARK_LOCATION
		using Location = std::source_location;
	#else // !__N_OVA_BARK_LOCATION
		struct Location {
			static consteval Location current() noexcept { return {}; }
		};
	#endif // __N_OVA_BARK_LOCATION
} // namespace Nova::bark