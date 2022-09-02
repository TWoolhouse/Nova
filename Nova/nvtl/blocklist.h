#pragma once
#include "meta/head.h"
#include "meta/concept.h"
#include "bark/bark.h"

namespace Nova::nvtl {

	template<typename T>
	class BlockList {
	public:
		struct Head {
			Head *previous, *next;
			size_t count;
			Head(Head* previous, Head* next, const size_t count) : previous(previous), next(next), count(count) {}
			Head(const Head& other, Head* previous=nullptr, Head* next=nullptr)
				: previous(previous), next(next), count(other.count) {}
			virtual ~Head() = default;

			struct block_iterator {
				using iterator_type = block_iterator;
				using difference_type = std::ptrdiff_t;
				using value_type = Head;
				using reference = value_type&;
				using pointer = value_type*;

				block_iterator() = default;
				block_iterator(pointer block) : curr(block) {}

				NODISCARD inline reference operator*() { return *curr; }
				NODISCARD inline pointer operator->() { return curr; }

				iterator_type& operator++() noexcept {
					curr = curr->next;
					return *this;
				}
				NODISCARD iterator_type operator++(int) noexcept {
					iterator_type tmp(*this);
					operator++();
					return tmp;
				}
				iterator_type& operator--() noexcept {
					curr = curr->previous;
					return *this;
				}
				NODISCARD iterator_type operator--(int) noexcept {
					iterator_type tmp(*this);
					operator--();
					return tmp;
				}

				NODISCARD inline bool operator!=(const iterator_type& other) const noexcept {
					return curr != other.curr;
				}
				NODISCARD inline bool operator==(const iterator_type& other) const noexcept {
					return !operator!=(other);
				}

			protected:
				pointer curr;
			};

			struct reverse_block_iterator {
				using iterator_type = reverse_block_iterator;
				using difference_type = Head::block_iterator::difference_type;
				using value_type = Head::block_iterator::value_type;
				using reference = Head::block_iterator::reference;
				using pointer = Head::block_iterator::pointer;

				reverse_block_iterator() = default;
				reverse_block_iterator(pointer block) : curr(block) {}

				NODISCARD inline reference operator*() {
					return *curr;
				}
				NODISCARD inline pointer operator->() {
					return curr;
				}

				iterator_type& operator++() noexcept {
					curr = curr->previous;
					return *this;
				}
				NODISCARD iterator_type operator++(int) noexcept {
					iterator_type tmp(*this);
					operator++();
					return tmp;
				}
				iterator_type& operator--() noexcept {
					curr = curr->next;
					return *this;
				}
				NODISCARD iterator_type operator--(int) noexcept {
					iterator_type tmp(*this);
					operator--();
					return tmp;
				}

				NODISCARD inline bool operator!=(const iterator_type& other) const noexcept {
					return curr != other.curr;
				}
				NODISCARD inline bool operator==(const iterator_type& other) const noexcept {
					return !operator!=(other);
				}

			protected:
				pointer curr;
			};

			struct iterator {
				using iterator_type = iterator;
				using difference_type = std::ptrdiff_t;
				using value_type = T;
				using reference = value_type&;
				using pointer = value_type*;

				iterator() = default;
				iterator(Head* block) : block(block), first(static_cast<Block<1>*>(block)->arr.data()), last(first + (block ? (block->count ? block->count : 1) : 0)), curr(first) {}
				iterator(Head* block, const bool) : block(block), first(static_cast<Block<1>*>(block)->arr.data()), last(first + (block ? (block->count ? block->count : 1) : 0)), curr(last) {}

				void set_block(Head* next) {
					block = next;
					first = reinterpret_cast<Block<1>*>(block)->arr.data();
					last = first + block->count;
				}

				NODISCARD inline reference operator*() const {
					return *curr;
				}
				NODISCARD inline pointer operator->() const noexcept {
					return curr;
				}

				iterator_type& operator++() {
					++curr;
					if (curr == last && block->next) {
						set_block(block->next);
						curr = first;
					}
					return *this;
				}
				NODISCARD iterator_type operator++(int) {
					iterator_type tmp(*this);
					operator++();
					return tmp;
				}
				iterator_type& operator--() {
					if (curr == first && block->previous) {
						set_block(block->previous);
						curr = last;
					}
					--curr;
					return *this;
				}
				NODISCARD iterator_type operator--(int) {
					iterator_type tmp(*this);
					operator--();
					return tmp;
				}

				NODISCARD inline bool operator!=(const iterator_type& other) const noexcept {
					return curr != other.curr;
				}
				NODISCARD inline bool operator==(const iterator_type& other) const noexcept {
					return !operator!=(other);
				}

			protected:
				Head* block;
				pointer first, last, curr;
			};

			using const_iterator = const iterator;
			using reverse_iterator = std::reverse_iterator<iterator>;
			using const_reverse_iterator = const std::reverse_iterator<const_iterator>;

			using const_block_iterator = const block_iterator;
			using const_reverse_block_iterator = const reverse_block_iterator;

		};

		template<size_t Count>
		struct Block : public Head {
			Block(Head* previous, Head* next) : Head(previous, next, Count) {}
			Block(Head* previous, Head* next, std::array<T, Count>&& arr)
				: Head(previous, next, Count), arr(std::forward<decltype(arr)>(arr)) {}
			template<typename ...Ts> requires (sizeof...(Ts) > 0) && meta::all_convertable<T, Ts...>
			Block(Head* previous, Head* next, Ts&&... args)
				: Head(previous, next, Count), arr({std::move(args)...}) {}
			Block(const Block& other, Head* previous=nullptr, Head* next=nullptr)
				: Head(previous, next, Count), arr(other.arr) {}
			std::array<T, Count> arr;
		};

	protected:
		Head *head, *tail;
	public:
		BlockList() : head(nullptr), tail(nullptr), blocks(*this) {};
		~BlockList() {
			clear();
		}

		using iterator = Head::iterator;
		using const_iterator = Head::const_iterator;
		using reverse_iterator = Head::reverse_iterator;
		using const_reverse_iterator = Head::const_reverse_iterator;

		NODISCARD inline iterator begin() { return iterator(head); }
		NODISCARD inline const_iterator cbegin() const { return const_iterator(head); }
		NODISCARD inline const_iterator begin() const { return cbegin(); }
		NODISCARD inline iterator end() { return iterator(tail, false); }
		NODISCARD inline const_iterator cend() const { return const_iterator(tail, false); }
		NODISCARD inline const_iterator end() const { return cend(); }

		NODISCARD inline reverse_iterator rbegin() { return reverse_iterator(end()); }
		//NODISCARD inline const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
		//NODISCARD inline const_reverse_iterator rbegin() const { return crbegin(); }
		NODISCARD inline reverse_iterator rend() { return reverse_iterator(begin()); }
		//NODISCARD inline const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }
		//NODISCARD inline const_reverse_iterator rend() const { return crend(); }

		struct blocks {
			constexpr blocks(BlockList& parent) : parent(parent) {}

			using iterator = Head::block_iterator;
			using const_iterator = Head::const_block_iterator;
			using reverse_iterator = Head::reverse_block_iterator;
			using const_reverse_iterator = Head::const_reverse_block_iterator;

			NODISCARD inline iterator begin() { return iterator(parent.head); }
			NODISCARD inline const_iterator cbegin() const { return const_iterator(parent.head); }
			NODISCARD inline const_iterator begin() const { return cbegin(); }
			NODISCARD inline iterator end() { return iterator(); }
			NODISCARD inline const_iterator cend() const { return const_iterator(); }
			NODISCARD inline const_iterator end() const { return cend(); }

			NODISCARD inline reverse_iterator rbegin() { return reverse_iterator(parent.tail); }
			//NODISCARD inline const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
			//NODISCARD inline const_reverse_iterator rbegin() const { return crbegin(); }
			NODISCARD inline reverse_iterator rend() { return reverse_iterator(); }
			//NODISCARD inline const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }
			//NODISCARD inline const_reverse_iterator rend() const { return crend(); }

		private:
			BlockList& parent;
		} blocks;

		//template<size_t Size>
		//void push_back(std::array<T, Size>&& arr) {
		//	if (!head) [[unlikely]] {
		//		head = tail = new Block<Size>(nullptr, nullptr, std::forward(arr));
		//	} else [[likely]] {
		//		tail->next = new Block<Size>(tail, nullptr, std::forward(arr));
		//		tail = tail->next;
		//	}
		//}

		template<typename ...Ts> requires (sizeof...(Ts) > 0) && meta::all_convertable<T, Ts...>
		Block<sizeof...(Ts)>* emplace_back(Ts&&... elems) {
			if (!head) [[unlikely]] {
				head = tail = new Block<sizeof...(Ts)>(nullptr, nullptr, std::forward<Ts>(elems)...);
			} else [[likely]] {
				tail->next = new Block<sizeof...(Ts)>(tail, nullptr, std::forward<Ts>(elems)...);
				tail = tail->next;
			}
			return reinterpret_cast<Block<sizeof...(Ts)>*>(tail);
		}

		template<size_t Size>
		Block<Size>* emplace_back(Block<Size>* block) {
			if (!head) [[unlikely]] {
				head = tail = new Block<Size>(*block);
			} else [[likely]] {
				tail->next = new Block<Size>(*block, tail, nullptr);
				tail = tail->next;
			}
			return reinterpret_cast<Block<Size>*>(tail);
		}

	protected:
		void remove(Head* ptr) {
			#ifdef NOVA_DEBUG
			bool flag = false;
			for (auto it = blocks.rbegin(), end = blocks.rend(); it != end; ++it) {
				if (it == ptr)	{
					flag = true;
					break;
				}
			}
			nova_assert(flag, "Block Pointer is not Valid!");
			#endif // NOVA_DEBUG

			((ptr == head) ? head : ptr->previous->next) = ptr->next;
			((ptr == tail) ? tail : ptr->next->previous) = ptr->previous;
			delete ptr;
		}
	public:
		inline void remove(const_iterator iter) { return remove(iter.block); }
		inline void remove(void* const ptr) { return remove(reinterpret_cast<Head*>(ptr)); }

		NODISCARD bool empty() noexcept {
			return head == nullptr;
		}

		void clear() noexcept {
			decltype(head) block = nullptr;
			while (head) {
				block = head->next;
				delete head;
				head = block;
			}
			tail = nullptr;
		}

	};

}
