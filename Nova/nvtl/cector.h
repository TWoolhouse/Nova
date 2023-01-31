#pragma once
#include "meta/head.h"

namespace Nova::nvtl {

	template<typename T>
	class Cector {
	public:
		using value_type = T;
		// TODO: Allow for other allocators
		using allocator_type = std::allocator<T>;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const reference;
		using pointer = std::allocator_traits<allocator_type>::pointer;
		using const_pointer = std::allocator_traits<allocator_type>::const_pointer;

		struct Iterator {
			using container = Cector<T>;
			using iterator_type = Iterator;
			using iterator_concept = std::contiguous_iterator_tag;
			using iterator_category = std::contiguous_iterator_tag;
			using value_type = container::value_type;
			using difference_type = container::difference_type;
			using pointer = container::pointer;
			using const_pointer = container::pointer;
			using reference = container::reference;
			using const_reference = container::reference;

			constexpr Iterator(pointer ptr) : ptr(ptr) {}
			constexpr Iterator(const Iterator&) = default;
			constexpr Iterator& operator=(const Iterator&) = default;
			constexpr Iterator(Iterator&&) = default;
			constexpr Iterator& operator=(Iterator&&) = default;
			constexpr ~Iterator() = default;

			constexpr auto operator<=>(const Iterator& other) const = default;

			constexpr reference operator*() const { return *ptr; }
			constexpr pointer operator->() { return ptr; }
			constexpr const_pointer operator->() const { return ptr; }

			constexpr Iterator& operator++() { ptr++; return *this; }
			constexpr Iterator& operator++(int) { auto tmp = *this; ++(*this); return tmp; }
			constexpr Iterator& operator--() { ptr--; return *this; }
			constexpr Iterator& operator--(int) { auto tmp = *this; --(*this); return tmp; }

			constexpr Iterator operator+(ptrdiff_t n) const { return ptr + n; }
			constexpr Iterator operator-(ptrdiff_t n) const { return ptr - n; }
			constexpr Iterator& operator+=(ptrdiff_t n) { ptr += n; return *this; }
			constexpr Iterator& operator-=(ptrdiff_t n) { ptr -= n; return *this; }
			constexpr reference operator[](ptrdiff_t n) const { return ptr[n]; };

		protected:
			pointer ptr;
		};

		struct ConstIterator {
			using container = Cector<T>;
			using iterator_type = ConstIterator;
			using iterator_concept = std::contiguous_iterator_tag;
			using iterator_category = std::contiguous_iterator_tag;
			using value_type = container::value_type;
			using difference_type = container::difference_type;
			using pointer = container::pointer;
			using const_pointer = container::pointer;
			using reference = container::reference;
			using const_reference = container::reference;

			constexpr ConstIterator(pointer ptr) : ptr(ptr) {}
			constexpr ConstIterator(const ConstIterator&) = default;
			constexpr ConstIterator& operator=(const ConstIterator&) = default;
			constexpr ConstIterator(ConstIterator&&) = default;
			constexpr ConstIterator& operator=(ConstIterator&&) = default;
			constexpr ~ConstIterator() = default;

			constexpr auto operator<=>(const ConstIterator& other) const = default;

			constexpr const_reference operator*() const { return *ptr; }
			constexpr const_pointer operator->() const { return ptr; }

			constexpr ConstIterator& operator++() { ptr++; return *this; }
			constexpr ConstIterator& operator++(int) { auto tmp = *this; ++(*this); return tmp; }
			constexpr ConstIterator& operator--() { ptr--; return *this; }
			constexpr ConstIterator& operator--(int) { auto tmp = *this; --(*this); return tmp; }

			constexpr ConstIterator operator+(ptrdiff_t n) const { return ptr + n; }
			constexpr ConstIterator operator-(ptrdiff_t n) const { return ptr - n; }
			constexpr ConstIterator& operator+=(ptrdiff_t n) { ptr += n; return *this; }
			constexpr ConstIterator& operator-=(ptrdiff_t n) { ptr -= n; return *this; }
			constexpr reference operator[](ptrdiff_t n) const { return ptr[n]; };

		protected:
			const_pointer ptr;
		};

		 using iterator = Iterator;
		 using const_iterator = ConstIterator;
		 using reverse_iterator = std::reverse_iterator<iterator>;
		 using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	public:
		constexpr Cector(size_type size) : m_size(size), array(allocator_type{}.allocate(m_size)) {
			auto it = array;
			auto end = it + m_size;
			for (; it < end; ++it)
				std::construct_at(it);
		}
		constexpr Cector(std::initializer_list<value_type> il) : m_size(il.size()), array(allocator_type{}.allocate(m_size)) {
			std::copy_n(std::data(il), il.size(), array);
		}
		template<typename ...Args>
		constexpr Cector(size_type size, Args&& ...args) : m_size(size), array(allocator_type{}.allocate(m_size)) {
			auto it = array;
			auto end = it + m_size;
			for (; it < end; ++it)
				// Cannot be forward<> as they are required for every iteration.
				std::construct_at(it, args...);
		}

		constexpr Cector(Cector&& other) noexcept : m_size(other.m_size), array(std::exchange(other.array, nullptr)) {}
		constexpr Cector& operator=(Cector&& other) noexcept {
			this->m_size = other.m_size;
			this->array = std::exchange(other.array, nullptr);
			return *this;
		}

		constexpr Cector(const Cector& other) : m_size(other.m_size), array(allocator_type{}.allocate(m_size)) {
			std::copy_n(other.array, m_size, array);
		}
		constexpr Cector& operator=(const Cector& other) noexcept {
			if (this != &other) {
				m_size = other.m_size;
				destroy();
				array = allocator_type{}.allocate(m_size);
				std::copy_n(other.array, m_size, array);
			}
			return *this;
		}

		constexpr ~Cector() {
			if (array)
				destroy();
		}

		constexpr size_type size() const noexcept { return m_size; }
		constexpr size_type max_size() const noexcept { return size(); }
		constexpr size_type capacity() const noexcept { return size(); }

		constexpr pointer data() { return array; }
		constexpr const const_pointer data() const { return array; }

		constexpr reference at(size_type pos) { if (pos >= size()) throw std::out_of_range(); return operator[](pos); }
		constexpr const_reference at(size_type pos) const { if (pos >= size()) throw std::out_of_range(); return operator[](pos); }
		constexpr reference operator[](size_type pos) {
			nova_cassert(pos < size(), "`pos` is greater than the size of the cector");
			return array[pos];
		}
		constexpr const_reference operator[](size_type pos) const {
			nova_cassert(pos < size(), "`pos` is greater than the size of the cector");
			return array[pos];
		}

		constexpr iterator begin() { return array; }
		constexpr iterator end() { return array + m_size; }
		constexpr const_iterator begin() const { return cbegin(); }
		constexpr const_iterator end() const { return cend(); }
		constexpr const_iterator cbegin() const { return array; }
		constexpr const_iterator cend() const { return array + m_size; }

		constexpr reverse_iterator rbegin() { return end(); }
		constexpr reverse_iterator rend() { return begin(); }
		constexpr const_reverse_iterator rbegin() const { return cend(); }
		constexpr const_reverse_iterator rend() const { return cbegin(); }
		constexpr const_reverse_iterator crbegin() const { return cend(); }
		constexpr const_reverse_iterator crend() const { return cbegin(); }

	protected:
		constexpr void destroy() {
			std::destroy_n(array, m_size);
			allocator_type{}.deallocate(array, m_size);
		}

	protected:
		size_type m_size;
		pointer array;
	};

} // namespace Nova::nvtl
