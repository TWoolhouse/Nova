#include "npch.h"
#include "abyss.h"
#include "app.h"

namespace Nova::abyss {

	void Initialize(const std::string_view& name) {
		constexpr auto api =
		#if defined(NOVA_ABYSS_VULKAN)
		"Vulkan";
		#endif // NOVA_ABYSS

		nova_bark_init("[Abyss] <{}>", api);
		new App();
	}
	void Terminate() {
		nova_bark_term("[Abyss]");
		delete App::I;
		App::I = nullptr;
	}

}
