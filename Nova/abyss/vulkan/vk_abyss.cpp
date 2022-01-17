#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "abyss.h"

namespace Nova::abyss {
	namespace vkn {

		Abyss::Abyss(const std::string_view& name) : cxt(name), device(cxt) {}

	}



	static vkn::Abyss* abyss;
	void Initialize(const std::string_view& name) {
		abyss = new vkn::Abyss(name);
	}
	void Terminate() {
		delete abyss;
	}

}
#endif // NOVA_ABYSS_VULKAN
