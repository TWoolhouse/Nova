#pragma once
#include "meta/head.h"

namespace Nova::abyss::exc {
	struct FrameResize : public std::exception {
		virtual const char* what() const noexcept {
			return "The Flight is invalid as the Frame is resizing!";
		}
	};
}
