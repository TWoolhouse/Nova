#pragma once
#include "meta/head.h"
#include "meta/concept.h"
#include "bark/bark.h"

namespace Nova::nvtl {

	template<typename T>
	class BlockList {
	protected:
		struct BlockHead {
			BlockHead *previous, *next;
			size_t count;
			BlockHead(BlockHead* previous, BlockHead* next, const size_t count) : previous(previous), next(next), count(count) {}
			BlockHead(const BlockHead& other, BlockHead* previous=nullptr, BlockHead* next=nullptr)
				: previous(previous), next(next), count(other.count) {}
			virtual ~BlockHead() = default;

			struct block_iterator {
				using iterator_type = block_iterator;
				using difference_type = std::ptrdiff_t;
				using value_type = BlockHead;
				using reference = value_type&;
				using pointer = value_type*;

				block_iterator() = default;
				block_iterator(pointer block) : curr(block) {}

				inline NODISCARD reference operator*() { return *curr; }
				inline NODISCARD pointer operator->() { return curr; }

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

				inline NODISCARD bool operator!=(const iterator_type& other) const noexcept {
					return curr != other.curr;
				}
				inline NODISCARD bool operator==(const iterator_type& other) const noexcept {
					return !operator!=(other);
				}

			protected:
				pointer curr;
			};

			struct reverse_block_iterator {
				using iterator_type = reverse_block_iterator;
				using difference_type = BlockHead::block_iterator::difference_type;
				using value_type = BlockHead::block_iterator::value_type;
				using reference = BlockHead::block_iterator::reference;
				using pointer = BlockHead::block_iterator::pointer;

				reverse_block_iterator() = default;
				reverse_block_iterator(pointer block) : curr(block) {}

				inline NODISCARD reference operator*() {
					return *curr;
				}
				inline NODISCARD pointer operator->() {
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

				inline NODISCARD bool operator!=(const iterator_type& other) const noexcept {
					return curr != other.curr;
				}
				inline NODISCARD bool operator==(const iterator_type& other) const noexcept {
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
				iterator(BlockHead* block) : block(block), first(static_cast<Block<1>*>(block)->buff.data()), last(first + (block ? (block->count ? block->count : 1) : 0)), curr(first) {}
				iterator(BlockHead* block, const bool) : block(block), first(static_cast<Block<1>*>(block)->buff.data()), last(first + (block ? (block->count ? block->count : 1) : 0)), curr(last) {}

				void set_block(BlockHead* next) {
					block = next;
					first = static_cast<Block<1>*>(block)->buff.data();
					last = first + block->count;
				}

				inline NODISCARD reference operator*() const {
					return *curr;
				}
				inline NODISCARD pointer operator->() const noexcept {
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

				inline NODISCARD bool operator!=(const iterator_type& other) const noexcept {
					return curr != other.curr;
				}
				inline NODISCARD bool operator==(const iterator_type& other) const noexcept {
					return !operator!=(other);
				}

			protected:
				BlockHead* block;
				pointer first, last, curr;
			};

			using const_iterator = const iterator;
			using reverse_iterator = std::reverse_iterator<iterator>;
			using const_reverse_iterator = const std::reverse_iterator<const_iterator>;

			using const_block_iterator = const block_iterator;
			using const_reverse_block_iterator = const reverse_block_iterator;

		};

		template<size_t Count>
		struct Block : public BlockHead {
			Block(BlockHead* previous, BlockHead* next) : BlockHead(previous, next, Count) {}
			Block(BlockHead* previous, BlockHead* next, std::array<T, Count>&& arr)
				: BlockHead(previous, next, Count), buff(std::forward<decltype(arr)>(arr)) {}
			template<typename ...Ts> requires (sizeof...(Ts) > 0) && meta::all_convertable<T, Ts...>
			Block(BlockHead* previous, BlockHead* next, Ts&&... args)
				: BlockHead(previous, next, Count), buff({std::move(args)...}) {}
			Block(const Block& other, BlockHead* previous=nullptr, BlockHead* next=nullptr)
				: BlockHead(previous, next, Count), buff(other.buff) {}
			std::array<T, Count> buff;
		};

	protected:
		BlockHead *first, *last;
	public:
		BlockList() : first(nullptr), last(nullptr), blocks(*this) {};
		~BlockList() {
			clear();
		}

		using iterator = BlockHead::iterator;
		using const_iterator = BlockHead::const_iterator;
		using reverse_iterator = BlockHead::reverse_iterator;
		using const_reverse_iterator = BlockHead::const_reverse_iterator;

		inline NODISCARD iterator begin() { return iterator(first); }
		inline NODISCARD const_iterator cbegin() const { return const_iterator(first); }
		inline NODISCARD const_iterator begin() const { return cbegin(); }
		inline NODISCARD iterator end() { return iterator(last, false); }
		inline NODISCARD const_iterator cend() const { return const_iterator(last, false); }
		inline NODISCARD const_iterator end() const { return cend(); }

		inline NODISCARD reverse_iterator rbegin() { return reverse_iterator(end()); }
		//inline NODISCARD const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
		//inline NODISCARD const_reverse_iterator rbegin() const { return crbegin(); }
		inline NODISCARD reverse_iterator rend() { return reverse_iterator(begin()); }
		//inline NODISCARD const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }
		//inline NODISCARD const_reverse_iterator rend() const { return crend(); }

		struct blocks {
			constexpr blocks(BlockList& parent) : parent(parent) {}

			using iterator = BlockHead::block_iterator;
			using const_iterator = BlockHead::const_block_iterator;
			using reverse_iterator = BlockHead::reverse_block_iterator;
			using const_reverse_iterator = BlockHead::const_reverse_block_iterator;

			inline NODISCARD iterator begin() { return iterator(parent.first); }
			inline NODISCARD const_iterator cbegin() const { return const_iterator(parent.first); }
			inline NODISCARD const_iterator begin() const { return cbegin(); }
			inline NODISCARD iterator end() { return iterator(); }
			inline NODISCARD const_iterator cend() const { return const_iterator(); }
			inline NODISCARD const_iterator end() const { return cend(); }

			inline NODISCARD reverse_iterator rbegin() { return reverse_iterator(parent.last); }
			//inline NODISCARD const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
			//inline NODISCARD const_reverse_iterator rbegin() const { return crbegin(); }
			inline NODISCARD reverse_iterator rend() { return reverse_iterator(); }
			//inline NODISCARD const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }
			//inline NODISCARD const_reverse_iterator rend() const { return crend(); }

		private:
			BlockList& parent;
		} blocks;

				template<size_t Size>
		void push_back(std::array<T, Size>&& arr) {
			if (!first) [[unlikely]] {
				first = last = new Block<Size>(nullptr, nullptr, std::forward(arr));
			} else [[likely]] {
				last->next = new Block<Size>(last, nullptr, std::forward(arr));
				last = last->next;
			}
		}

		template<typename ...Ts> requires (sizeof...(Ts) > 0) && meta::all_convertable<T, Ts...>
		Block<sizeof...(Ts)>* emplace_back(Ts&&... elems) {
			if (!first) [[unlikely]] {
				first = last = new Block<sizeof...(Ts)>(nullptr, nullptr, std::forward<Ts>(elems)...);
			} else [[likely]] {
				last->next = new Block<sizeof...(Ts)>(last, nullptr, std::forward<Ts>(elems)...);
				last = last->next;
			}
			return static_cast<Block<sizeof...(Ts)>*>(last);
		}

		template<size_t Size>
		Block<Size>* emplace_back(Block<Size>* block) {
			using BlockS = Block<Size>;
			if (!first) [[unlikely]] {
				first = last = new BlockS(*block);
			} else [[likely]] {
				last->next = new BlockS(*block, last, nullptr);
				last = last->next;
			}
			return static_cast<BlockS*>(last);
		}

	protected:
		void remove(BlockHead* ptr) {
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

			((ptr == first) ? first : ptr->previous->next) = ptr->next;
			((ptr == last) ? last : ptr->next->previous) = ptr->previous;
			delete ptr;
		}
	public:
		inline void remove(void* const ptr) { return remove(static_cast<BlockHead*>(ptr)); }

		NODISCARD bool empty() noexcept {
			return first == nullptr;
		}

		void clear() noexcept {
			decltype(first) block = nullptr;
			while (first) {
				block = first->next;
				delete first;
				first = block;
			}
			last = nullptr;
		}

	};

}
