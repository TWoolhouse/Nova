#pragma once
#include "head.h"

namespace Nova::meta::str {

	template<std::ranges::forward_range Rng>
	std::string join(Rng&& rng, const std::string& delimiter = ", ") {
		std::stringstream stream;
		if (auto it = std::ranges::begin(rng), e = std::ranges::end(rng); it != e) {
			stream << *it++;
			for (; it != e; ++it) stream << delimiter << *it;
		}
		return stream.str();
	}

}
