#pragma once
#include "meta/head.h"
#include "null.h"

namespace Nova::abyss::spec {

	template<typename T>
	concept Target = Null<T>;

}
