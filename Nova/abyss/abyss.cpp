#include "npch.h"
#include "abyss.h"
#include "app.h"

namespace Nova::abyss {

	void Initialize(const core::Information& app_info) {
		constexpr auto api =
		#if defined(NOVA_ABYSS_VULKAN)
		"Vulkan";
		#endif // NOVA_ABYSS

		nova_bark_init("[Abyss] <{}>", api);
		new App(app_info);
	}
	void Terminate() {
		nova_bark_term("[Abyss]");
		delete App::I;
		App::I = nullptr;
	}

}
