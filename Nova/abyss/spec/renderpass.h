#pragma once
#include "meta/head.h"
#include "null.h"
#include "abyss/target.h"

namespace Nova::abyss::spec {

	template<typename T>
	concept Renderpass = Null<T> && std::same_as<decltype(T::target), abyss::Targets>;

}
