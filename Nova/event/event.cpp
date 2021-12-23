#include "npch.h"
#include "event.h"

namespace Nova::Event {
	
	typename decltype(Base::callbacks) Base::callbacks;

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

	bool Base::fire(const Type etype) {
		for (uint8_t i = 0; i < Base::callbacks.size(); i++) {
			if (bit_isset(etype, i)) {
				for (auto& func : Base::callbacks[i]) {
					if (func(*this)) return true;
				}
			}
		}
		return false;
	}

}
