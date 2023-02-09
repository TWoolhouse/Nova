#pragma once
#include "head.h"

namespace Nova::meta::str {

	template<std::ranges::forward_range Rng>
	std::string join(Rng&& rng, const std::string& delimiter = ", ") {
		std::stringstream stream;
		if (auto it = std::ranges::begin(rng), e = std::ranges::end(rng); it != e) {
			stream << *it++;
			for (; it != e; ++it) stream << delimiter << *it;
		}
		return stream.str();
	}

	/**
	 * to_string.hpp - Provides compile-time integer-to-string conversion.
	 * Written by Clyne Sullivan.
	 * https://github.com/tcsullivan/constexpr-to-string
	 */
	namespace __I::tcsullivan {

		inline constexpr char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

		/**
		 * @struct to_string_t
		 * @brief Provides the ability to convert any integral to a string at compile-time.
		 * @tparam N Number to convert
		 * @tparam base Desired base, can be from 2 to 36
		 */
		template<auto N, int base, typename char_type> requires std::is_integral_v<decltype(N)> && (base > 1 && base < sizeof(digits))
		class to_string_t {

			static consteval auto buf_size() noexcept {
				unsigned int len = N > 0 ? 1 : 2;
				for (auto n = N; n; len++, n /= base);
				return len;
			}

			// The lambda calculates what the string length of N will be, so that `buf`
			// fits to the number perfectly.
			char_type buf[buf_size()] = {};

			public:
			/**
			 * Constructs the object, filling `buf` with the string representation of N.
			 */
			constexpr to_string_t() noexcept {
				auto ptr = end();
				*--ptr = '\0';
				if (N != 0) {
					for (auto n = N; n; n /= base)
						*--ptr = digits[(N < 0 ? -1 : 1) * (n % base)];
					if (N < 0)
						*--ptr = '-';
				} else {
					buf[0] = '0';
				}
			}

			// Support implicit casting to `char *` or `const char *`.
			constexpr operator char_type *() noexcept { return buf; }
			constexpr operator const char_type *() const noexcept { return buf; }

			constexpr auto size() const noexcept { return sizeof(buf) / sizeof(buf[0]); }
			// Element access
			constexpr auto data() noexcept { return buf; }
			constexpr const auto data() const noexcept { return buf; }
			constexpr auto& operator[](unsigned int i) noexcept { return buf[i]; }
			constexpr const auto& operator[](unsigned int i) const noexcept { return buf[i]; }
			constexpr auto& front() noexcept { return buf[0]; }
			constexpr const auto& front() const noexcept { return buf[0]; }
			constexpr auto& back() noexcept { return buf[size() - 1]; }
			constexpr const auto& back() const noexcept { return buf[size() - 1]; }
			// Iterators
			constexpr auto begin() noexcept { return buf; }
			constexpr const auto begin() const noexcept { return buf; }
			constexpr auto end() noexcept { return buf + size(); }
			constexpr const auto end() const noexcept { return buf + size(); }
		};

	} // namespace __I::tcsullivan

	// Provides the ability to convert any integral to a string at compile-time.
	template<auto N, int base = 10, typename char_type = char>
	constexpr __I::tcsullivan::to_string_t<N, base, char_type> as;

}
