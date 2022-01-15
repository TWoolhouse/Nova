#pragma once
#include "meta/head.h"
#include "blip/blip.h"
#include "log.h"

namespace Nova::bark {

	struct Timer : public blip::Timer {
		std::string_view msg;
		Timer() : msg("Temporary"sv) {}
		Timer(const std::string_view& msg) : msg(msg) {}
		~Timer() {
			update();
			nova_bark_debug("[Timer] {}: {}", msg, elapsed());
		}
	};

}

#ifdef __N_OVA_BARK_STATE_DEBUG
#define nova_bark_timer(message) ::Nova::bark::Timer CONCAT(__b_ark__t_imer_, __COUNTER__) {message}
#else // !__N_OVA_BARK_STATE_DEBUG
#define nova_bark_timer(message)
#endif // __N_OVA_BARK_STATE_DEBUG
