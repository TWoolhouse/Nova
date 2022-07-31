#pragma once

namespace Nova::meta::def {

	namespace build {

		// NOVAPI DLL Import / Export
	#ifdef NOVA_BUILD_STATIC
	#error Nova does not currently support static linking!
		constexpr bool Static = true;
		constexpr bool Export = false;
	#define NOVAPI
	#else // !NOVA_BUILD_STATIC
		constexpr bool Static = false;
	#ifdef NOVA_BUILD_EXPORT
		constexpr bool Export = true;
	#define NOVAPI __declspec(dllexport)
	#else // !NOVA_BUILD_EXPORT
		constexpr bool Export = false;
	#define NOVAPI __declspec(dllimport)
	#endif // NOVA_BUILD_EXPORT
	#endif // NOVA_BUILD_STATIC

	#ifdef NOVA_BUILD_EXPORT
		constexpr bool Self = true;
	#define NOVA_BUILD_SELF
	#else // !NOVA_BUILD_EXPORT
		constexpr bool Self = false;
	#undef NOVA_BUILD_SELF
	#endif // NOVA_BUILD_EXPORT

	}

// NOVA_ DEBUG / RELEASE
#ifdef DEBUG
#define NOVA_DEBUG
	constexpr bool Debug = true;
	constexpr bool Release = false;
#else // !DEBUG
#define NOVA_RELEASE
	constexpr bool Debug = false;
	constexpr bool Release = true;
#endif // DEBUG

}
