#pragma once
#include "meta/head.h"
#include "interface/flock.h"
#include "nvtl/cector.h"

namespace Nova::abyss {

	template<typename T>
	class Flock : private nvtl::Cector<T> {
		using Super = nvtl::Cector<T>;
	public:
		using value_type = Super::value_type;
		template<typename ...Args>
		Flock(Args&& ...args) : Super(interface::flock_size(), std::forward<Args>(args)...) {}

		Super::reference operator[](abyss::Flight& flight) {
			return Super::operator[](0);
		}
	};

} // namespace Nova::abyss
