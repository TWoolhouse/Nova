#include "npch.h"
#ifdef NOVA_ABYSS_OPENGL
#include "opengl.h"
#include "app.h"
#include "../abyss.h"

namespace Nova::abyss {

	void Initialize(const std::string_view& name) {
		nova_bark_init("[Abyss] <OpenGL> ...");
		nova_assert(!gl::Application::I, "Creating Multiple OpenGL Applications");
		new gl::Application(name);
		nova_bark_init("[Abyss] Done!");
	}
	void Terminate() {
		nova_bark_term("[Abyss] ...");
		delete gl::Application::I;
		gl::Application::I = nullptr;
		nova_bark_term("[Abyss] Done!");
	}

	bool& acquire() { return App->acquire(); }
	void  release() { return App->release(); }

}

#endif // NOVA_ABYSS_OPENGL
