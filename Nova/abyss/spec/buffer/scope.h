#pragma once
#include "meta/head.h"

namespace Nova::abyss::spec::buffer {

	template<typename T>
	concept Scope = std::is_enum_v<T> && requires {
		T::Bind;
		T::Read;
		T::Write;
	};

}