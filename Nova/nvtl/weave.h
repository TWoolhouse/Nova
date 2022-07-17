#pragma once
#include "meta/head.h"
#include "bark/bark.h"

namespace Nova::nvtl {

	template<typename T, size_t Count, typename Allocator = std::allocator<T>>
	class Weave {
	public:
		using value_type = T;
		using allocator_type = Allocator;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = typename std::allocator_traits<allocator_type>::pointer;
		using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;
		using size_type = allocator_type::size_type;
		using difference_type = allocator_type::difference_type;
		// using iterator = void;
		// using const_iterator = void;
		// using reverse_iterator = std::reverse_iterator<iterator>;
		// using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		static_assert(std::same_as<T, value_type>&& std::same_as<value_type, allocator_type::value_type>, "Mismataching container and allocator type!");

		explicit Weave(const allocator_type& alloc = allocator_type()) : allocator_row(alloc) {}
		Weave(const Weave&) = delete; // Currently copying is not trivial to work out
		Weave& operator=(const Weave&) = delete;
		Weave(Weave&&) = default;
		Weave& operator=(Weave&&) = default;

		struct Tracker;
		~Weave() { clear(); }

		static consteval size_type size() noexcept { return Count; }
		static consteval size_type max_size() noexcept { return size(); }

		using Token = size_t;

	protected:
		struct Head;
		struct Head {
			Head() = default;
			Head(const Head& other) = default;
			Head(Head&& o) noexcept : next(std::move(o.next)), prev(std::move(o.prev)) {
				prev->next = this;
				next->prev = this;
			}
			Head(Head* next, Head* prev) : next(next), prev(prev) {}

			Head* next = nullptr;
			Head* prev = nullptr;
		};

		struct Tracker : public Head {
			Tracker(std::size_t size) : size(size) {}
			std::size_t size;
		};

		struct Row : public Head {
			Row() = default;
			Row(const Row&) = default;
			Row(Row&&) = default;
			Row(const value_type& obj) : object(obj) {}
			Row(value_type&& obj) : object(std::move(obj)) {}
			using value_type = value_type;
			value_type object;
		};

		class Thread : protected Head {
			friend class Weave;
		public:
			using value_type = value_type;
			using reference = reference;
			using const_reference = const_reference;
			using pointer = pointer;
			using const_pointer = const_pointer;
			using difference_type = std::ptrdiff_t;

			Thread() : Head(this, this) {}

			constexpr void emplace_back(Head* row) {
				row->prev = this->prev;
				row->next = this;
				this->prev->next = row;
				this->prev = row;
			}

			static constexpr void remove(Head* row) {
				row->next->prev = row->prev;
				row->prev->next = row->next;
			}
		protected:
			template<bool const_>
			class Iterator {
				using internal_type = std::conditional_t<const_, const Head, Head>;
				using external_type = std::conditional_t<const_, const Row, Row>;
			public:
				Iterator() = default;
				Iterator(internal_type* ptr) : m_ptr(ptr) {}

				using iterator_category = std::bidirectional_iterator_tag;
				using value_type = std::conditional_t<const_, const typename value_type, typename value_type>;
				using difference_type = std::ptrdiff_t;
				using pointer = value_type*;
				using reference = value_type&;

				reference operator*() { return reinterpret_cast<external_type*>(m_ptr)->object; }
				pointer operator->() { return reinterpret_cast<external_type*>(m_ptr); }
				Iterator& operator++() {
					m_ptr = m_ptr->next;
					return *this;
				}
				Iterator& operator++(int) {
					Iterator tmp = *this;
					++(*this);
					return tmp;
				}
				Iterator& operator--() {
					m_ptr = m_ptr->prev;
					return *this;
				};
				Iterator& operator--(int) {
					Iterator tmp = *this;
					--(*this);
					return tmp;
				}

				friend bool operator==(const Iterator& a, const Iterator& b) = default;

			protected:
				internal_type* m_ptr;
			};
		public:
			using iterator = Iterator<false>;
			using const_iterator = Iterator<true>;
			using reverse_iterator = std::reverse_iterator<iterator>;
			using const_reverse_iterator = std::reverse_iterator<const_iterator>;

			iterator begin() { return iterator(this->next); }
			iterator end() { return iterator(this); }
			const_iterator begin() const { return const_iterator(this->next); }
			const_iterator end() const { return const_iterator(this); }
			const_iterator cbegin() const { return begin(); }
			const_iterator cend() const { return end(); }

			reverse_iterator rbegin() { return reverse_iterator(this); }
			reverse_iterator rend() { return reverse_iterator(this->next); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(this); }
			const_reverse_iterator rend() const { return const_reverse_iterator(this->next); }
			const_reverse_iterator crbegin() const { return rbegin(); }
			const_reverse_iterator crend() const { return rend(); }
		};

	public:
		constexpr auto& at(size_type pos) {
			if (pos >= size())
				throw std::out_of_range{ "Invalid index argument" };
			return threads[pos];
		}
		constexpr auto& at(size_type pos) const {
			if (pos >= size())
				throw std::out_of_range{ "Invalid index argument" };
			return threads[pos];
		}
		constexpr auto& operator[](size_type pos) {
			nova_assert(pos < size(), "Invalid index argument");
			return threads[pos];
		}
		constexpr auto& operator[](size_type pos) const {
			nova_assert(pos < size(), "Invalid index argument");
			return threads[pos];
		}

		auto begin() const { return threads.begin(); }
		auto end() const { return std::prev(threads.end()); }
		auto cbegin() const { return threads.cbegin(); }
		auto cend() const { return std::prev(threads.cend()); }
		auto rbegin() const { return std::next(threads.rbegin()); }
		auto rend() const { return threads.rend(); }
		auto crbegin() const { return std::next(threads.crbegin()); }
		auto crend() const { return threads.crend(); }

	public:
		template<std::size_t Extent = std::dynamic_extent>
		using Ticket = std::span<Row, Extent>;

	protected:
		using AllocatorRow = std::allocator_traits<Allocator>::template rebind_alloc<Row>;
		using AllocatorTraitsRow = std::allocator_traits<AllocatorRow>;
		AllocatorRow allocator_row;

		template<typename Pair>
			requires requires(Pair p) {
				{ p.first } -> std::convertible_to<Token>;
				{ p.second } -> std::convertible_to<value_type>;
		}
		constexpr auto construct_row(Row* row, Pair&& obj) {
			AllocatorTraitsRow::construct(allocator_row, row, std::move(obj.second));
			nova_assert(obj.first < Count, "Weave Insert Invalid Thread ID");
			threads[obj.first].emplace_back(row);
		}

		template<typename A, typename B, typename... Args>
		constexpr auto construct_row(Row* row, A&& token, B&& obj, Args&&... args) {
			construct_row(row++, std::pair{ token, obj });
			if constexpr (sizeof...(Args)) {
				return construct_row(row, args...);
			}
		}

		constexpr auto destroy_row(Row* row) {
			Thread::remove(row);
			AllocatorTraitsRow::destroy(allocator_row, row);
		}
		constexpr auto destroy_all(Tracker* tracker) {
			for (auto row = reinterpret_cast<Row*>(tracker) + extra_space(); row != reinterpret_cast<Row*>(tracker) + tracker->size; ++row)
				destroy_row(row);
		}

		consteval static auto extra_space() {
			if constexpr (sizeof(Tracker) > sizeof(Row)) {
				auto diff = (sizeof(Tracker) - sizeof(Row));
				return diff / sizeof(Row) + (diff % sizeof(Row) != 0 ? 1 : 0);
			} else
				return 1;
		}

		constexpr auto allocate(size_t size) {
			constexpr auto extra = extra_space();
			auto rows = AllocatorTraitsRow::allocate(allocator_row, size + extra);
			std::construct_at<Tracker>(reinterpret_cast<Tracker*>(rows), size + extra);
			threads[Count].emplace_back(rows);
			return rows + extra;
		}
		template<std::size_t Extent>
		constexpr auto deallocate(Ticket<Extent> ticket) {
			deallocate(reinterpret_cast<Tracker*>(ticket.data() - extra_space()));
		}
		constexpr auto deallocate(Tracker* tracker) {
			Thread::remove(tracker);
			std::destroy_at<Tracker>(tracker);
			AllocatorTraitsRow::deallocate(allocator_row, reinterpret_cast<AllocatorTraitsRow::pointer>(tracker), tracker->size);
		}

	public:
		template<typename T>
			requires std::convertible_to<T, value_type>
		constexpr Ticket<1> push_back(Token token, T&& value) {
			auto row = allocate(1);
			construct_row(row, std::pair{ token, std::forward<T>(value) });
			return Ticket<1>{row, 1};
		}

		template<typename... Args>
			requires meta::interlace < meta::lace <
				[]<typename T>() { return std::convertible_to<Token, T>; },
					[]<typename T>() { return std::convertible_to<T, value_type>; }
			> , Args... >
		constexpr auto push_back(Args&&... args) -> Ticket<sizeof...(Args) / 2> {
			constexpr auto Size = sizeof...(Args) / 2;
			auto rows = allocate(Size);
			Ticket<Size> ticket{ rows, Size };
			construct_row(rows++, std::forward<Args>(args)...);
			return ticket;
		}

		constexpr Ticket<> push_back(std::initializer_list<std::pair<Token, typename Row::value_type>>&& list) {
			auto rows = allocate(list.size());
			Ticket ticket{ rows, list.size() };
			for (auto&& obj : list)
				construct_row(rows++, std::forward<decltype(obj)>(obj));
			return ticket;
		}

		template<typename Iter>
		constexpr Ticket<> push_back(Iter first, Iter last, size_t size) {
			auto rows = allocate(size);
			Ticket ticket{ rows, size };
			for (; first != last; ++first)
				construct_row(rows++, std::move(*first));
			return ticket;
		}

		template<std::size_t Extent>
		constexpr void remove(Ticket<Extent> ticket) {
			for (auto&& row : ticket) {
				destroy_row(&row);
			}
			deallocate(ticket);
		}

		constexpr void clear() {
			auto ptr = reinterpret_cast<Tracker*>(threads[Count].next);
			const auto end = reinterpret_cast<Tracker*>(&threads[Count]);
			while (ptr != end) {
				auto next = ptr->next;
				destroy_all(ptr);
				deallocate(ptr);
				ptr = reinterpret_cast<Tracker*>(std::move(next));
			}
		}

	protected:
		std::array<Thread, Count + 1> threads;
	};

} // namespace Nova::nvtl
