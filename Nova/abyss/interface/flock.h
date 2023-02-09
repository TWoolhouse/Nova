#pragma once
#include "meta/head.h"
#include "abyss/flight.h"

namespace Nova::abyss::interface {

	NOVAPI size_t flock_size();
	//template<typename T>
	//concept FlockValidate = requires (T flock, abyss::Flight& flight) {
	//	typename T::value_type;
	//	{ flock[flight] } -> std::convertible_to<typename T::value_type>;
	//};

	template<typename T>
	class Flock {
	public:
		inline static auto size() { return flock_size(); }
	private:
		//static_assert(FlockValidate<T>, "Flock Specialisation does not conform to the interface");
	};

};