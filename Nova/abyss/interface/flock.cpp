#include "npch.h"
#include "flock.h"
#include "abyss/abyss.h"

namespace Nova::abyss::interface {

	size_t flock_size() {
		// TODO: Centralise the number of flights.
		return nova_abyss_app->tower.MAX_FLIGHTS;
	}

} // Nova::abyss::interface
