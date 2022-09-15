#pragma once
#include "head.h"

namespace Nova::meta {

	constexpr size_t align_to(size_t position, size_t alignment) {
		const auto diff = position % alignment; 
		if (diff == 0) return position;
		return position + (alignment - diff);
	}

}