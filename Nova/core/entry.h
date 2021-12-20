#include "npch.h"
#include "application.h"

#ifdef NOVA_ENTRY
int NOVA_MAIN(int argc, char const* argv[]) {
	auto app = Nova::Application::Create();
	app->execute();
	delete app;
	return 0;
}
#endif
