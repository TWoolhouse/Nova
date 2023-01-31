#include "npch.h"
#include "assert.h"
#include "log.h"
#include "location_str.h"

namespace Nova::bark {

#ifdef __N_OVA_BARK_ASSERT
		void assertion(bool condition, const std::string_view msg, const Location location) {
			if (condition) [[likely]]; else {
				nova_bark_fatal("{}\nAssertion: {}", location_string(location), msg);
			}
		}
		constexpr void assertion_constexpr(bool condition, const std::string_view msg, const Location location) {
			NOVA_MC_UNUSED(condition);
			NOVA_MC_UNUSED(msg);
			NOVA_MC_UNUSED(location);
			return;
		}
	#endif // __N_OVA_BARK_ASSERT

} // namespace Nova::bark
