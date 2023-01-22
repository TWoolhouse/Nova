#pragma once

/* List of all options that can be changed via #defines

//----<BUILD>----//

// NOVA_BUILD_SELF
#define NOVA_BUILD_SELF

// NOVA_BUILD_OPTIMISE_<OPT>
#define NOVA_BUILD_OPTIMISE_DEBUG
#define NOVA_BUILD_OPTIMISE_RELEASE

// NOVA_BUILD_LINK_<OPT>
#define NOVA_BUILD_LINK_STATIC
#define NOVA_BUILD_LINK_DYNAMIC

//-----<API>-----//

// NOVA_ABYSS_<API>
#define NOVA_ABYSS_VULKAN
#define NOVA_ABYSS_DIRECTX
#define NOVA_ABYSS_OPENGL

// NOVA_MLB_<API>
#define NOVA_MLB_GLM
#define NOVA_MLB_NOVA

// NOVA_WINDOW_<API>
#define NOVA_WINDOW_NATIVE
#define NOVA_WINDOW_GLFW

//-----<BARK>-----//

#define __N_OVA_BARK_ASSERT 0 / 1

#define __N_OVA_BARK_FILE 0 / 1
#define __N_OVA_BARK_CONSOLE 0 / 1
#define __N_OVA_BARK_LOCATION 0 / 1

#define __N_OVA_BARK_WARN 0 / 1
#define __N_OVA_BARK_TODO 0 / 1
#define __N_OVA_BARK_UNIMPLEMENTED 0 / 1
#define __N_OVA_BARK_INIT 0 / 1
#define __N_OVA_BARK_INFO 0 / 1
#define __N_OVA_BARK_TRACE 0 / 1
#define __N_OVA_BARK_DEBUG 0 / 1
#define __N_OVA_BARK_TEMP 0 / 1

//-----<ABYSS>-----//

// #define __N_OVA_ABYSS_DEBUG 0 / 1
// #define __N_OVA_ABYSS_CHECK 0 / 1

// #define __N_OVA_ABYSS_BARK_WARN 0 / 1
// #define __N_OVA_ABYSS_BARK_INFO 0 / 1
// #define __N_OVA_ABYSS_BARK_DEBUG 0 / 1

*/

// DEFAULT CONFIG

#define __N_OVA_ABYSS_BARK_DEBUG 0

#ifndef NOVA_BUILD_OPTIMISE_DEBUG

	// BARK
	#define __N_OVA_BARK_ASSERT 0
	#define __N_OVA_BARK_FILE 1
	#define __N_OVA_BARK_CONSOLE 0
	#define __N_OVA_BARK_LOCATION 1

	#define __N_OVA_BARK_TODO 1
	#define __N_OVA_BARK_UNIMPLEMENTED 1
	#define __N_OVA_BARK_INFO 1
	#define __N_OVA_BARK_INIT 0
	#define __N_OVA_BARK_TRACE 0
	#define __N_OVA_BARK_DEBUG 0
	#define __N_OVA_BARK_TEMP 0

	// ABYSS
	#define __N_OVA_ABYSS_DEBUG 0
	#define __N_OVA_ABYSS_CHECK 0
	#define __N_OVA_ABYSS_BARK_INFO 0
	#define __N_OVA_ABYSS_BARK_DEBUG 0

#endif // NOVA_BUILD_OPTIMISE_DEBUG
