#pragma once
#include "defines.h"

namespace Nova::meta::def {

//-----------------------------------------------------------------//
//-----------------------------NOVA_OS-----------------------------//
//-----------------------------------------------------------------//

#pragma region NOVA_OS

// NOVA_OS_<API>

#if defined(NOVA_OS_WINDOWS)
	// Supported!
	// #error NOVA_OS_WINDOWS is not currently supported!
#elif defined(NOVA_OS_LINUX)
	#error NOVA_OS_LINUX is not currently supported!
#elif defined(NOVA_OS_UNIX)
	#error NOVA_OS_UNIX is not currently supported!
#elif defined(NOVA_OS_APPLE)
	#error NOVA_OS_APPLE is not currently supported!
#endif // NOVA_OS_PLATFORM

#pragma endregion

namespace build {

//-----------------------------------------------------------------//
//-------------------------NOVA_BUILD_SELF-------------------------//
//-----------------------------------------------------------------//

#pragma region NOVA_BUILD_SELF

constexpr bool self =
#if defined(NOVA_BUILD_SELF)
	true
#else
	false
#endif // NOVA_BUILD_SELF
;
#pragma endregion

//-----------------------------------------------------------------//
//-----------------------NOVA_BUILD_OPTIMISE-----------------------//
//-----------------------------------------------------------------//

#pragma region NOVA_BUILD_OPTIMISE

enum class Optimise : uint8_t {
	Debug,
	Release,
};

constexpr auto optimise = Optimise::
#if !(defined(NOVA_BUILD_OPTIMISE_DEBUG) || defined(NOVA_BUILD_OPTIMISE_RELEASE))
	#ifdef DEBUG
		#define NOVA_BUILD_OPTIMISE_DEBUG
	#else // !DEBUG
		#define NOVA_BUILD_OPTIMISE_RELEASE
	#endif // DEBUG
#elif defined(NOVA_BUILD_OPTIMISE_DEBUG) && defined(NOVA_BUILD_OPTIMISE_RELEASE)
#error Multiple Nova Build Optimise Options Selected!
#endif // NOVA_BUILD_OPTIMISE

#if defined(NOVA_BUILD_OPTIMISE_DEBUG)
	Debug
	// #error NOVA_BUILD_OPTIMISE_DEBUG is not currently supported!
#elif defined(NOVA_BUILD_OPTIMISE_RELEASE)
	Release
	// #error NOVA_BUILD_OPTIMISE_RELEASE is not currently supported!
#endif // NOVA_BUILD_OPTIMISE
;
#pragma endregion

//-----------------------------------------------------------------//
//-------------------------NOVA_BUILD_LINK-------------------------//
//-----------------------------------------------------------------//

#pragma region NOVA_BUILD_LINK

enum class Link : uint8_t {
	Static,
	Dynamic,
};

constexpr auto link = Link::
#if !(defined(NOVA_BUILD_LINK_STATIC) || defined(NOVA_BUILD_LINK_DYNAMIC))
#error No Nova Build Link Option Selected! NOVA_BUILD_LINK_<OPT> \
OPT: STATIC, DYNAMIC
#elif defined(NOVA_BUILD_LINK_STATIC) && defined(NOVA_BUILD_LINK_DYNAMIC)
#error Multiple Nova Build Link Options Selected!
#endif // NOVA_BUILD_LINK

#if defined(NOVA_BUILD_LINK_STATIC)
	Static
	// #error NOVA_BUILD_LINK_STATIC is not currently supported!
#elif defined(NOVA_BUILD_LINK_DYNAMIC)
	Dynamic
	// #error NOVA_BUILD_LINK_DYNAMIC is not currently supported!
#endif // NOVA_BUILD_LINK
;
#pragma endregion

} // namespace build

//-----------------------------------------------------------------//
//---------------------------NOVA_ABYSS----------------------------//
//-----------------------------------------------------------------//

#pragma region NOVA_ABYSS

enum class Abyss : uint8_t{
	Vulkan,
	DirectX,
	OpenGL,
};

constexpr auto abyss = Abyss::
#if !(defined(NOVA_ABYSS_VULKAN) || defined(NOVA_ABYSS_OPENGL) || defined(NOVA_ABYSS_DIRECTX))
#error No Nova Abyss Graphics Rendering API Selected! NOVA_ABYSS_<API> \
API: VULKAN, OPENGL, DIRECTX
#elif 0\
|| ( defined(NOVA_ABYSS_VULKAN) && defined(NOVA_ABYSS_OPENGL) ) \
|| ( defined(NOVA_ABYSS_VULKAN) && defined(NOVA_ABYSS_DIRECTX) ) \
|| ( defined(NOVA_ABYSS_OPENGL) && defined(NOVA_ABYSS_DIRECTX) )
#error Multiple Nova Abyss Graphics Rendering APIs Selected!
#endif // NOVA_ABYSS_API

#if defined(NOVA_ABYSS_VULKAN)
	Vulkan
	// #error NOVA_ABYSS_VULKAN is not currently supported!
#elif defined(NOVA_ABYSS_OPENGL)
	OpenGL
	#error NOVA_ABYSS_OPENGL is not currently supported!
#elif defined(NOVA_ABYSS_DIRECTX)
	DirectX
	#error NOVA_ABYSS_DIRECTX is not currently supported!
#endif // NOVA_ABYSS_API
;
#pragma endregion

//-----------------------------------------------------------------//
//----------------------------NOVA_MLB-----------------------------//
//-----------------------------------------------------------------//

#pragma region NOVA_MLB

enum class Mlb : uint8_t {
	Nova,
	GLM
};

constexpr auto mlb = Mlb::
#if !(defined(NOVA_MLB_NOVA) || defined(NOVA_MLB_GLM))
#error No Nova MLB Maths API Selected! NOVA_MLB_<API> \
API: NOVA, GLM
#elif defined(NOVA_MLB_NOVA) && defined(NOVA_MLB_GLM)
#error Multiple Nova MLB Maths APIs Selected!
#endif // NOVA_MLB_API

#if defined(NOVA_MLB_NOVA)
	Nova
	#error NOVA_MLB_NOVA is not currently supported!
#elif defined(NOVA_MLB_GLM)
	GLM
	// #error NOVA_MLB_GLM is not currently supported!
#endif // NOVA_MLB_API
;
#pragma endregion

//-----------------------------------------------------------------//
//---------------------------NOVA_WINDOW---------------------------//
//-----------------------------------------------------------------//

#pragma region NOVA_WINDOW

enum class Window : uint8_t {
	Native,
	GLFW,
};

constexpr auto window = Window::
#if !(defined(NOVA_WINDOW_NATIVE) || defined(NOVA_WINDOW_GLFW))
#error No Nova Window API Selected! NOVA_WINDOW_<API> \
API: NATIVE, GLFW
#elif defined(NOVA_WINDOW_NATIVE) && defined(NOVA_WINDOW_GLFW)
#error Multiple Nova Window APIs Selected!
#endif // NOVA_WINDOW_API

#if defined(NOVA_WINDOW_NATIVE)
	Native
	// #error NOVA_WINDOW_NATIVE is not currently supported!
	#if defined(NOVA_OS_WINDOWS)
		// Supported!
	#else
		#error NOVA_WINDOW_NATIVE is not currently supported on the OS!
	#endif // NOVA_OS
#elif defined(NOVA_WINDOW_GLFW)
	GLFW
	#error NOVA_WINDOW_GLFW is not currently supported!
#endif // NOVA_MLB_API
;
#pragma endregion

//-----------------------------------------------------------------//
//---------------------------NOVA_DEBUG----------------------------//
//-----------------------------------------------------------------//

#pragma region NOVA_DEBUG

constexpr bool debug =
#ifdef NOVA_BUILD_OPTIMISE_DEBUG
	true
	#define NOVA_DEBUG
#else // !NOVA_BUILD_OPTIMISE_DEBUG
	false
	#undef NOVA_DEBUG
#endif // NOVA_BUILD_OPTIMISE_DEBUG
;
#pragma endregion

//-----------------------------------------------------------------//
//-----------------------------NOVAPI------------------------------//
//-----------------------------------------------------------------//

#pragma region NOVAPI

#ifdef NOVA_BUILD_LINK_STATIC
	#define NOVAPI
#else // !NOVA_BUILD_LINK_STATIC
	#ifdef NOVA_BUILD_SELF
		#if defined(NOVA_TC_MSVC)
			#define NOVAPI __declspec(dllexport)
		#else // !NOVA_TC
			#error NOVA_BUILD_LINK_DYNAMIC is not currently supported on this toolchain
		#endif // NOVA_TC
	#else // !NOVA_BUILD_SELF
		#if defined(NOVA_TC_MSVC)
			#define NOVAPI __declspec(dllimport)
		#else // !NOVA_TC
			#error NOVA_BUILD_LINK_DYNAMIC is not currently supported on this toolchain
		#endif // NOVA_TC
	#endif // NOVA_BUILD_SELF
#endif // NOVA_BUILD_LINK_STATIC

#pragma endregion

} // namspace Nova::meta::def
