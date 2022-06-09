#include "npch.h"
#ifdef NOVA_ABYSS_OPENGL
#include "app.h"

namespace Nova::abyss::gl {

	decltype(Application::I) Application::I;

	Application::Application(const std::string_view& name) {
		I = this;
	}

	Application::~Application() {}

	bool& Application::acquire() {
		return active;
	}

	void Application::release() {}

}

#endif // NOVA_ABYSS_OPENGL
