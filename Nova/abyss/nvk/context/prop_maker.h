#pragma once
#include "vk.h"
#include "props.h"

namespace Nova::abyss::nvk {

	prop::Setup make_prop_setup() {
		return prop::Setup {
			.app_name = "Application Name",
			.layers = {
				#ifdef __N_OVA_ABYSS_DEBUG
				"VK_LAYER_KHRONOS_validation",
				#endif // __N_OVA_ABYSS_DEBUG
			},
			.extensions_instance = {
				VK_KHR_SURFACE_EXTENSION_NAME,

				#if defined(NOVA_OS_WINDOWS)
				"VK_KHR_win32_surface",
				#elif defined(NOVA_OS_LINUX)
				"VK_KHR_xcb_surface",
				#endif // OS Extensions

				#ifdef __N_OVA_ABYSS_DEBUG
				VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
				#endif // __N_OVA_ABYSS_DEBUG
			},
			.extensions_device = {
				VK_KHR_SWAPCHAIN_EXTENSION_NAME,
			},
			.device_features = {
				.geometryShader = true,
				.samplerAnisotropy = true,
			},
		};
	}

}
