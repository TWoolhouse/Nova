#pragma once

namespace Nova::meta::def {

	// NOVAPI DLL Import / Export
#ifdef NOVA_EXPORT
#define NOVAPI __declspec(dllexport)
	constexpr bool Export = true;
#else
#define NOVAPI __declspec(dllimport)
	constexpr bool Export = false;
#endif

	// NOVA_ DEBUG / RELEASE
#ifdef DEBUG
#define NOVA_DEBUG
	constexpr bool Debug = true;
	constexpr bool Release = false;
#else
#define NOVA_RELEASE
	constexpr bool Debug = false;
	constexpr bool Release = true;
#endif

}