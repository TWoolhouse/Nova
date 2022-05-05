#pragma once
#include "meta/head.h"

namespace Nova::abyss {

	NOVAPI void Initialize(const std::string_view& name);
	NOVAPI void Terminate();

	NOVAPI bool& acquire();
	NOVAPI void  release();

}
