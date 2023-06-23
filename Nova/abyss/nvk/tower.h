#pragma once
#include "meta/head.h"
#include "flight.h"
#include "abyss/flight.h"
#include "abyss/renderpass.h"

namespace Nova::abyss::nvk {

	class Tower {
	public:
		static constexpr uint8_t MAX_FLIGHTS = 3;

		Tower();
		~Tower();

		abyss::Flight& acquire();
		INLINE void release(abyss::Flight& flight) { return release(static_cast<Flight&>(flight)); }

		abyss::Renderpass renderpass;

	protected:
		std::array<Flight, MAX_FLIGHTS> flights;
		std::remove_const_t<decltype(MAX_FLIGHTS)> current_flight = 0;

		void release(Flight& flight);
		Flight& next_flight();

		void main_pass_begin(Flight& flight);
		void main_pass_end(Flight& flight);
		void sub_buffer_begin(Flight& flight);
		void sub_buffer_end(Flight& flight);

		void submit(Flight& flight);

	};

} // namespace Nova::abyss
