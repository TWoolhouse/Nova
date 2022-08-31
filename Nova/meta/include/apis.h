#pragma once
#include "defines.h"

//--------------------------------------------------------------\\
//-------------------------NOVA_MLB_API-------------------------\\
//--------------------------------------------------------------\\

// NOVA_MLB_<API>
// API:
//     NOVA
//     GLM

#if !(defined(NOVA_MLB_NOVA) || defined(NOVA_MLB_GLM))
#error No Nova MLB Maths API Selected! NOVA_MLB_<API> \
API: NOVA, GLM
#elif defined(NOVA_MLB_NOVA) && defined(NOVA_MLB_GLM)
#error Multiple Nova MLB Maths APIs Selected!
#endif // NOVA_MLB_API

#if defined(NOVA_MLB_NOVA)
#error NOVA_MLB_NOVA is not currently supported!
#elif defined(NOVA_MLB_GLM)
// Supported!
// #error NOVA_MLB_GLM is not currently supported!
#endif // NOVA_MLB_API

//----------------------------------------------------------------\\
//-------------------------NOVA_ABYSS_API-------------------------\\
//----------------------------------------------------------------\\

// NOVA_ABYSS_<API>
// API:
//     VULKAN
//     OPENGL
//     DIRECTX

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
// Supported!
// #error NOVA_ABYSS_VULKAN is not currently supported!
#elif defined(NOVA_ABYSS_OPENGL)
#error NOVA_ABYSS_OPENGL is not currently supported!
#elif defined(NOVA_ABYSS_DIRECTX)
#error NOVA_ABYSS_DIRECTX is not currently supported!
#endif // NOVA_ABYSS_API

//---------------------------------------------------------------\\
//----------------------------NOVA_OS----------------------------\\
//---------------------------------------------------------------\\

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

//---------------------------------------------------------------\\
//-------------------------NOVA_WINDOW-------------------------\\
//---------------------------------------------------------------\\

// NOVA_WINDOW_<API>

#if !(defined(NOVA_WINDOW_NATIVE) || defined(NOVA_WINDOW_GLFW))
#error No Nova Window API Selected! NOVA_WINDOW_<API> \
API: NATIVE, GLFW
#elif defined(NOVA_WINDOW_NATIVE) && defined(NOVA_WINDOW_GLFW)
#error Multiple Nova Window APIs Selected!
#endif // NOVA_WINDOW_API

#if defined(NOVA_WINDOW_NATIVE)
// Supported!
// #error NOVA_WINDOW_NATIVE is not currently supported!
#if defined(NOVA_OS_WINDOWS)
// Supported!
#else
#error NOVA_WINDOW_NATIVE is not currently supported on the OS!
#endif // NOVA_OS
#elif defined(NOVA_WINDOW_GLFW)
#error NOVA_WINDOW_GLFW is not currently supported!
#endif // NOVA_MLB_API
