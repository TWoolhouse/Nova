#pragma once
#include "meta/head.h"

namespace Nova::nvtl::alloc {

	template<typename T, size_t N>
	class Bump {
	public:
		using value_type = T;

		//constexpr Bump() noexcept : Bump(nullptr, nullptr) {}
		constexpr Bump(void* begin, size_t size) noexcept : Bump(begin, reinterpret_cast<std::byte*>(begin) + size) {}
		constexpr Bump(void* begin, void* end) noexcept : begin(reinterpret_cast<std::byte*>(begin)), end(reinterpret_cast<std::byte*>(end)), ptr(this->end) {}

		template<typename U, size_t N_>
		friend class Bump;
		template<class U> constexpr Bump(const Bump<U, N>& o) noexcept : begin(o.begin), end(o.end), ptr(o.ptr) {
			nova_bark_debug("Copy");
		}

		template<typename U>
		struct rebind { using other = Bump<U, N>; };

		T* allocate(const size_t n) {
			nova_bark_debug("{} Allocate {} = {}B on {}B", __FUNCTION__, n, sizeof(T) * n, alignof(T));
			auto obj = reinterpret_cast<uintmax_t>(ptr - n * sizeof(T)) & ~(alignof(T) - 1);
			if (obj < reinterpret_cast<uintmax_t>(begin))
				throw std::bad_alloc{};
			nova_bark_trace("{} -> {} = {}",
				(void*)ptr,
				(void*)reinterpret_cast<std::byte*>(obj),
				std::distance(reinterpret_cast<std::byte*>(obj), ptr)
			);
			ptr = reinterpret_cast<std::byte*>(obj);
			return reinterpret_cast<T*>(obj);
		}
		constexpr void deallocate(T* const p, size_t n) const noexcept {
			nova_bark_debug("{} Deallocate {}", __FUNCTION__, n);
		}

		inline constexpr bool operator=(const Bump& other) { return end == other.end && ptr == other.ptr; }

		inline constexpr auto max_size() const { return std::distance(begin, end); }
		inline constexpr auto space() const { return std::distance(begin, ptr); }

	protected:
		std::byte* begin, * end, * ptr;
	};



	namespace span {

		template<typename T>
		class Bump {
		public:
			using value_type = T;

			template<typename U, size_t Extent>
			constexpr Bump(const std::span<U, Extent>& span) noexcept : Bump(span.data(), span.extent) {}
			constexpr Bump(void* begin, size_t size) noexcept : Bump(begin, reinterpret_cast<std::byte*>(begin) + size) {}
			constexpr Bump(void* begin, void* end) noexcept : begin(reinterpret_cast<std::byte*>(begin)), end(reinterpret_cast<std::byte*>(end)), ptr(this->end) {}

			Bump(const Bump&) = default;
			Bump& operator=(const Bump&) = default;
			Bump(Bump&&) = default;
			Bump& operator=(Bump&&) = default;

			template<typename U>
			friend class Bump;
			template<class U> constexpr Bump(const Bump<U>& o) noexcept : begin(o.begin), end(o.end), ptr(o.ptr) {}

			T* allocate(const size_t n) {
				nova_bark_debug("{} Allocate {} = {}B on {}B", __FUNCTION__, n, sizeof(T) * n, alignof(T));
				auto obj = reinterpret_cast<uintmax_t>(ptr - n * sizeof(T)) & ~(alignof(T) - 1);
				if (obj < reinterpret_cast<uintmax_t>(begin))
					throw std::bad_alloc{};
				nova_bark_trace("{} -> {} = {}",
					(void*)ptr,
					(void*)reinterpret_cast<std::byte*>(obj),
					std::distance(reinterpret_cast<std::byte*>(obj), ptr)
				);
				ptr = reinterpret_cast<std::byte*>(obj);
				return reinterpret_cast<T*>(obj);
			}
			constexpr void deallocate(T* const p, size_t n) const noexcept {
				nova_bark_debug("{} Deallocate {}", __FUNCTION__, n);
			}

			inline constexpr bool operator==(const Bump& other) { return end == other.end; }

			inline constexpr auto max_size() const { return std::distance(begin, end); }
			inline constexpr auto space() const { return std::distance(begin, ptr); }

		protected:
			std::byte* begin, * end, * ptr;
		};

	}

}
