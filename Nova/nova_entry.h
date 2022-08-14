#pragma once
#ifndef NOVA_MAIN
#include "core/application.h"
#endif // !NOVA_MAIN

#ifdef NOVA_ENTRY
int NOVA_MAIN(int argc, char const* argv[]) {
	using EntryApp = ::NOVA_ENTRY;
	static_assert(std::is_base_of_v<Nova::core::Application, EntryApp> && std::is_default_constructible_v<EntryApp>,
		"NOVA_ENTRY must be a default constructible sub class of application");
	EntryApp app;
	app.execute();
	return 0;
}
#else // !NOVA_ENTRY
#error NOVA_ENTRY is not defined before including the entry point.
#endif // NOVA_ENTRY
