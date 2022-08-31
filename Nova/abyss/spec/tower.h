#pragma once
#include "meta/head.h"
#include "null.h"
#include "abyss/flight.h"
#include "abyss/renderpass.h"

namespace Nova::abyss::spec {

	template<typename T>
	concept Tower = Null<T> && requires (T tower, abyss::Flight& flight) {
		requires std::is_default_constructible_v<T>;

		{ tower.acquire() } -> std::same_as<abyss::Flight&>;
		tower.release(flight);
		requires std::same_as<decltype(T::renderpass), abyss::Renderpass>;
	};

}
