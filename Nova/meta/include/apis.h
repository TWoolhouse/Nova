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
#endif // NOVA_MLB_API

//----------------------------------------------------------------\\
//-------------------------NOVA_ABYSS_API-------------------------\\
//----------------------------------------------------------------\\

// NOVA_ABYSS_<API>
// API:
//     VULKAN
//     OPENGL
//     DIRECTX

#ifdef NOVA_EXPORT
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
#elif defined(NOVA_ABYSS_OPENGL)
#error NOVA_ABYSS_OPENGL is not currently supported!
#elif defined(NOVA_ABYSS_DIRECTX)
#error NOVA_ABYSS_DIRECTX is not currently supported!
#endif // NOVA_ABYSS_API
#endif // NOVA_EXPORT