#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "../abyss.h"
#include "app.h"

namespace Nova::abyss {

	void Initialize(const std::string_view& name) {
		nova_bark_init("[Abyss] <Vulkan> ...");
		{
			nova_assert(!vkn::Application::I, "Creating Multiple Vulkan Applications!");
			nvk_tracec("Application");
			new vkn::Application(name);
		}
		nova_bark_init("[Abyss] Done!");
	}
	void Terminate() {
		nova_bark_term("[Abyss] ...");
		delete vkn::Application::I;
		vkn::Application::I = nullptr;
		nova_bark_term("[Abyss] Done!");
	}

	bool& acquire() {
		return App->acquire();
	}

	void release() {
		return App->release();
	}

}
#endif // NOVA_ABYSS_VULKAN
