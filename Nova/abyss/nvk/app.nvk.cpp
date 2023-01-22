#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "abyss/app.h"

#include "context/setup_props_temp.h"

namespace Nova::abyss {

	App::App(const core::Information& info) : App(info, nvk::make_setup_props()) {}

}

#endif // NOVA_ABYSS_VULKAN
