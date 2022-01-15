#pragma once
#include "meta/head.h"
#include "nvtl/blocklist.h"

#define nova_eden_bind(func, member) ::std::bind(func, &member, std::placeholders::_1)

template<typename E> requires std::is_enum_v<E>
NODISCARD inline constexpr bool operator&(const E a, const E b) {
	return static_cast<std::underlying_type_t<E>>(a) & static_cast<std::underlying_type_t<E>>(b);
}

namespace Nova::eden {

	using Ticket = void* const;

	template<typename D> requires std::is_enum_v<D>
	struct Event {
		using Eden = Event;
		using Descriptor = D;

		Event() = default;
		Event(const Descriptor desc) : desc(desc) {}

		// Descirptor of the Event Type
		static constexpr Descriptor descriptor = Descriptor();
		// Descriptor of the event
		Descriptor desc;

		template<typename E> requires std::derived_from<E, Eden>
		inline E* cast() {
			return desc & E::descriptor ? static_cast<E*>(this) : nullptr;
		}
	};

	template<typename Event, size_t C> requires std::derived_from<Event, eden::Event<typename Event::Descriptor>> && (C > 0)
	class Dispatcher {
	protected:
		using Descriptor = Event::Descriptor;
		using DType = std::underlying_type_t<Descriptor>;
		using FuncType = std::function<bool(Event&)>;
		std::array<nvtl::BlockList<FuncType>, C> lists;

		constexpr bool bit_isset(const Descriptor bitset, const DType index) {
			return (static_cast<DType>(bitset) & (1 << index));
		}
	public:
		Dispatcher() {}

		template<typename F, typename T>
		const Ticket subscribe(const Descriptor desciptor, F func, T& instance) {
			return subscribe(desciptor, nova_eden_bind(func, instance));
		};

		template<typename ...Fs>
		const Ticket subscribe(const Descriptor descriptor, const Fs&... functions) {
			decltype(lists[0].emplace_back(functions...)) ptr = nullptr;
			for (DType i = 0; i < lists.size(); ++i) {
				if (bit_isset(descriptor, i)) {
					if (ptr) {
						lists[i].emplace_back(ptr);
					} else {
						ptr = lists[i].emplace_back(functions...);
					}
				}
			}
			return ptr;
		}

		bool fire(Event& event) {
			for (DType i = 0; i < lists.size(); ++i) {
				if (bit_isset(event.desc, i)) {
					for (auto& func : lists[i]) {
						if (func(event)) return true;
					}
				}
			}
			return false;
		}

		//void remove(Ticket ticket) {
		//	lists
		//}

	};

}
