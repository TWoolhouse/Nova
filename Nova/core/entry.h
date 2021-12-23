#pragma once
#include "npch.h"
#include "application.h"

#ifdef NOVA_ENTRY
int NOVA_MAIN(int argc, char const* argv[]) {
	static_assert(std::is_base_of_v<Nova::Application, NOVA_ENTRY> && std::is_default_constructible_v<NOVA_ENTRY>,
		"NOVA_ENTRY must be a default constructible sub class of application");
	NOVA_ENTRY app;
	app.execute();
	return 0;
}
#endif
