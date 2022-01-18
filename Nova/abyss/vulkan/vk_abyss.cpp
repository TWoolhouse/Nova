#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "abyss.h"

namespace Nova::abyss {
	namespace vkn {

		Abyss::Abyss(const std::string_view& name) : cxt(name), device(cxt), swapchain(cxt, device, 1280, 720) {}

	}



	static vkn::Abyss* abyss;
	void Initialize(const std::string_view& name) {
		nova_bark_init("[Abyss] <Vulkan> ...");
		abyss = new vkn::Abyss(name);
		nova_bark_init("[Abyss] Done!");
	}
	void Terminate() {
		nova_bark_term("[Abyss] ...");
		delete abyss;
		nova_bark_term("[Abyss] Done!");
	}

}
#endif // NOVA_ABYSS_VULKAN
