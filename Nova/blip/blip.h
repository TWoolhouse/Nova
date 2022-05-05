#pragma once
#include "meta/head.h"
#include <chrono>

namespace Nova::blip {

	using ClockType = std::chrono::steady_clock;
	using Unit = std::chrono::duration<double>;
	using Time = std::chrono::time_point<ClockType, Unit>;
	inline NODISCARD static Time now() noexcept { return std::chrono::time_point_cast<Unit>(ClockType::now()); }

	struct Base {};

	struct Delta : public Base {
		Time prev, now;
		Unit delta;

		void update() {
			prev = now;
			now = blip::now();
			delta = now - prev;
		}

		inline NODISCARD constexpr operator Unit() const noexcept { return delta; }
		inline NODISCARD constexpr operator double() const noexcept { return delta.count(); }
	};

	struct Timer : public Base {
		Time start = now(), last = now();
		inline NODISCARD constexpr Unit elapsed() const noexcept {
			return last - start;
		};
		inline void update() noexcept {
			last = now();
		}
	};

	struct Clock : public Delta {
		Time start;
		Clock() : Delta(), start(prev) {}

		inline NODISCARD constexpr Unit elapsed() const noexcept {
			return now - start;
		}

	};

}

template<typename CharT>
struct std::formatter<Nova::blip::Delta, CharT> : public std::formatter<Nova::blip::Unit, CharT> {
	template<typename FormatContext>
	auto format(Nova::blip::Delta time, FormatContext& fc) {
		return std::formatter<Nova::blip::Unit, CharT>::format(time.delta, fc);
	}
};
template<typename CharT>
struct std::formatter<Nova::blip::Timer, CharT> : public std::formatter<Nova::blip::Unit, CharT> {
	template<typename FormatContext>
	auto format(Nova::blip::Timer time, FormatContext& fc) {
		return std::formatter<Nova::blip::Unit, CharT>::format(time.elapsed(), fc);
	}
};
