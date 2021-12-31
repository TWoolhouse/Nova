#pragma once
#include "npch.h"
#include <chrono>

namespace Nova {

	struct Clock {
		Clock(const double physics = 1.f / 240.f)
			: time_physics(physics), time_prev(), time_now(), time_dt(fsec(time_now - time_now).count()) {
			update();
		};
		inline double dt() const { return time_dt; };
		constexpr double phys() const { return time_physics; };
		void update() {
			time_prev = std::move(time_now);
			time_now = ClockType::now();
			time_dt = fsec(time_now - time_prev).count();
		}
	protected:
		using ClockType = std::chrono::steady_clock;
		using fsec = std::chrono::duration<double>;

		std::chrono::time_point<ClockType, fsec> time_prev, time_now;
		double time_dt;
		double time_physics;
	};

}