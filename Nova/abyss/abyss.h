#pragma once
#include "meta/head.h"
#include "app.h"
#include "core/info.h"

namespace Nova::abyss {

	NOVAPI void Initialize(const core::Information& app_info);
	NOVAPI void Terminate();

}

#define nova_abyss_app ::Nova::abyss::App::I
