#pragma once
#include "meta/head.h"
#include "interface/flock.h"
#include "nvtl/cector.h"

#ifdef NOVA_ABYSS_VULKAN
#include "nvk/flight.h"
#endif


namespace Nova::abyss {

	template<typename T>
	class Flock : public nvtl::Cector<T> {
		using Super = nvtl::Cector<T>;
	public:
		using value_type = Super::value_type;
		template<typename ...Args>
		Flock(Args&& ...args) : Super(interface::flock_size(), std::forward<Args>(args)...) {}

		Super::reference operator[](abyss::Flight& flight) {
			#ifdef NOVA_ABYSS_VULKAN
			// FIXME: This is a hack to get the flock to work with the flight as the frame index does not line up with the out of use flock item.
			return Super::operator[](static_cast<nvk::Flight&>(flight).swapchain_frame_index % interface::flock_size());
			#endif
			// return Super::operator[](0);
		}
	};

} // namespace Nova::abyss
