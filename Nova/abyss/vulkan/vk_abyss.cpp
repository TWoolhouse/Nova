#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "../abyss.h"
#include "context.h"
#include "device.h"

namespace Nova::abyss {

	void Initialize(const std::string_view& name) {
		abyss::vkn::Context aby{ name };
		abyss::vkn::Device device(aby);
	}

	void Terminate() {

	}

}
#endif // NOVA_ABYSS_VULKAN
