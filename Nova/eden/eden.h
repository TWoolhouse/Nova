#pragma once
#include "meta/head.h"
#include "nvtl/weave.h"
#include "meta/function.h"

#define nova_eden_bind(func, member) ::std::bind(func, &member, std::placeholders::_1)

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

		inline constexpr bool is(Descriptor descriptor) {
			return static_cast<bool>(desc & descriptor);
		}
		template<typename E> requires std::derived_from<E, Eden>
		inline constexpr E* cast() {
			return is(E::descriptor) ? static_cast<E*>(this) : nullptr;
		}

	};

	template<typename Event, size_t C>
		requires std::derived_from<Event, eden::Event<typename Event::Descriptor>> && (C > 0)
	class Dispatcher {
	protected:
		using Descriptor = Event::Descriptor;
		using DType = std::underlying_type_t<Descriptor>;
		using Stype = meta::smallest::uint<C>;
		using FuncType = std::function<bool(Event&)>;
		using Container = nvtl::Weave<FuncType, C>;

		Container container;

		inline static constexpr bool bit_isset(const Descriptor bitset, const DType index) {
			return (static_cast<DType>(bitset) & (1 << index));
		}

	public:
		Dispatcher() = default;

		using TicketOrphan = Container::template Ticket<>;
		struct Ticket {
			friend Dispatcher;
			Ticket() = default;
			Ticket(const Ticket&) = delete;
			Ticket& operator=(const Ticket&) = delete;
			Ticket(Ticket&& o) : ticket(std::move(o.ticket)), parent(std::exchange(o.parent, nullptr)) {}
			Ticket& operator=(Ticket&& o) {
				using std::swap;
				swap(this->ticket, o.ticket);
				swap(this->parent, o.parent);
				return *this;
			};

			~Ticket() {
				_remove();
			}

			// Detaches the Ticket from the scope
			constexpr TicketOrphan orphan() { parent = nullptr; return ticket; }
			constexpr void remove() { _remove(); parent = nullptr; }
		protected:
			INLINE constexpr void _remove() {
				if (parent)
					parent->remove(ticket);
			}
			Ticket(TicketOrphan ticket, Container& container) : ticket(ticket), parent(&container) {}
		protected:
			TicketOrphan ticket;
			Container* parent = nullptr;
		};

	protected:
		static constexpr std::pair<size_t, std::array<Stype, C>> decode_descriptor(Descriptor desc) {
			std::array<Stype, C> arr;
			size_t pos = 0;
			for (Stype i = 0; i < arr.size(); ++i) if (bit_isset(desc, i)) {
				arr[pos++] = i;
			}
			if (!pos)
				throw std::domain_error("Event Descriptor has no valid events to subscribe to!");
			return { pos, std::move(arr) };
		}

		template<typename Rng>
		inline constexpr auto commit(Rng&& range, size_t size) {
			return container.push_back(range.begin(), range.end(), size);
		}

	public:
		template<typename F>
		NODISCARD Ticket subscribe(Descriptor event, F&& func) {
			auto&& [count, buckets] = decode_descriptor(event);
			return { commit(
				std::span{ buckets.data(), count } | std::views::transform([&](auto&& desc) { return std::pair{ desc, func }; }),
				count
			), container };
		}

		NODISCARD Ticket subscribe(std::initializer_list<std::pair<Descriptor, FuncType>>&& list) {
			decltype(decode_descriptor({})) count_indices;
			auto view = list | std::views::transform([&](auto&& pair) {
				count_indices = decode_descriptor(pair.first);
				return std::views::transform(std::span{ count_indices.second.data(), count_indices.first }, [&](const auto index) {
					return std::pair{ index, pair.second };
				});
			}) | std::views::join;
			std::vector<std::pair<Stype, FuncType>> vec;
			vec.reserve(list.size());
			for (auto&& p : view)
				vec.push_back(std::move(p));
			return { commit(
				vec,
				vec.size()
			), container };
		}

		inline bool fire(Event&& event) { return fire(event); }
		bool fire(Event& event) {
			for (Stype i = 0; i < C; ++i) if (bit_isset(event.desc, i))
				for (auto& func : container[i])
					// It could return early and not let every event type get managed
					if (func(event)) return true; // TODO: How should this work
			return false;
		}

		inline void remove(TicketOrphan ticket) {
			Ticket{ ticket, container };
			// ~Ticket()
		}
		inline void remove(Ticket& ticket) {
			ticket.remove();
		}
		inline void remove(Ticket&& ticket) {
			ticket.remove();
		}

		void clear() {
			container.clear();
		}

	};

}
