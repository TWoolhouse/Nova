#include "npch.h"
#include "event.h"

namespace Nova::event {

	decltype(dispatcher) dispatcher;

	bool Handle::fire() {
		return dispatcher.fire(*this);
	}

}
