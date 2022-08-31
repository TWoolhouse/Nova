#pragma once
#include "meta/head.h"
#include "app.h"

namespace Nova::abyss {

	NOVAPI void Initialize(const std::string_view& name);
	NOVAPI void Terminate();

}

#define nova_abyss_app ::Nova::abyss::App::I
