#pragma once
#include "meta/head.h"
#include "nvtl/blocklist.h"

#define nova_eden_bind(func, member) ::std::bind(func, &member, std::placeholders::_1)

template<typename E> requires std::is_enum_v<E>
inline NODISCARD constexpr bool operator&(const E a, const E b) {
	return static_cast<std::underlying_type_t<E>>(a) & static_cast<std::underlying_type_t<E>>(b);
}

namespace Nova::eden {

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
		using Container = nvtl::BlockList<FuncType>;
		std::array<Container, C> list;

		inline constexpr bool bit_isset(const Descriptor bitset, const DType index) {
			return (static_cast<DType>(bitset) & (1 << index));
		}

	public:
		Dispatcher() {}

		struct Ticket {
			friend Dispatcher;
			Ticket() = default;
			Ticket(Descriptor descriptor) : descriptor(descriptor), blocks() {}
		protected:
			Descriptor descriptor;
			std::vector<void*> blocks;
		};

		template<typename F, typename T>
		Ticket subscribe(const Descriptor desciptor, F func, T& instance) {
			return subscribe(desciptor, nova_eden_bind(func, instance));
		};

		template<typename ...Fs>
		Ticket subscribe(const Descriptor descriptor, const Fs&... functions) {
			Ticket ticket{};
			for (DType i = 0; i < list.size(); ++i) {
				if (bit_isset(descriptor, i)) {
					ticket.blocks.emplace_back(list[i].emplace_back(functions...));
				}
			}
			return ticket;
		}

		bool fire(Event& event) {
			for (DType i = 0; i < list.size(); ++i) {
				if (bit_isset(event.desc, i)) {
					for (auto& func : list[i]) {
						if (func(event)) return true;
					}
				}
			}
			return false;
		}

		inline void remove(std::initializer_list<Ticket> tickets) {
			for (auto& ticket : tickets) {
				remove(ticket);
			}
		}

		void remove(Ticket ticket) {
			auto it = ticket.blocks.begin();
			for (DType i = 0; i < list.size(); ++i) {
				if (bit_isset(ticket.descriptor, i)) {
					list[i].remove(*it++);
				}
			}
		}

		void clear() {
			for (auto& list : list) {
				list.clear();
			}
		}

	};

}
