#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "abyss/app.h"

#include "context/prop_maker.h"

namespace Nova::abyss {

	App::App() : App(nvk::make_prop_setup()) {}

}

#endif // NOVA_ABYSS_VULKAN
