#include "npch.h"
#include "event.h"

namespace Nova::event {

	typename decltype(Base::callbacks) Base::callbacks;
	typename decltype(Register::counter) Register::counter = 0;

	constexpr bool bit_isset(const Type bitset, const TypeSize index) {
		return (static_cast<TypeSize>(bitset) & (1 << index));
	}

	void Register::enroll(const Type tag) {
		for (TypeSize i = 0; i < Base::callbacks.size(); i++) {
			if (bit_isset(tag, i)) {
				Base::callbacks[i].emplace_back(*this);
			}
		}
	}

	bool Base::fire() {
		for (uint8_t i = 0; i < Base::callbacks.size(); i++) {
			if (bit_isset(tag, i)) {
				for (auto& func : Base::callbacks[i]) {
					if (func(*this)) return true;
				}
			}
		}
		return false;
	}

}

