#pragma once
#include "meta/head.h"

namespace Nova::abyss::spec {

	struct null {};

	template<typename T>
	concept Null = !std::same_as<T, null>;

}