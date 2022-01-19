#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "instance.h"
#include "debug.h"

constexpr auto engine_name = "Nova"sv;

namespace Nova::abyss::vkn {

	void log_enumerations() {
		auto extensions = vk::enumerateInstanceExtensionProperties();
		nova_bark_debug("VK Availble Extensions:");
		for (const auto& ext : extensions) {
			nova_bark_debug("\tProperty: {}", ext.extensionName);
		}

		nova_bark_debug("VK Availble Layers:");
		auto lps = vk::enumerateInstanceLayerProperties();
		for (const auto& lp : lps) {
			nova_bark_debug("\tProperty: {}", lp.layerName);
		}
	}

	inline void platform_extensions(std::vector<cstr>& extensions) {
		#if defined(NOVA_OS_WINDOWS)
		extensions.emplace_back("VK_KHR_win32_surface");
		#elif defined(NOVA_OS_LINUX)
		extensions.emplace_back("VK_KHR_xcb_surface");
		#endif // OS Extensions
	}

	void create_instance(Context& cxt, const std::string_view& name) {
		nvk_tracec("Instance");

		vk::ApplicationInfo app_info{
			name.data(),
			VK_MAKE_API_VERSION(0, 0, 1, 0),
			engine_name.data(),
			VK_MAKE_API_VERSION(0, 0, 1, 0),
			VK_API_VERSION_1_2
		};

		std::vector<cstr> layers{};
		std::vector<cstr> extensions{
			VK_KHR_SURFACE_EXTENSION_NAME
		};

		platform_extensions(extensions);

		// Debug Extensions & Layers
		#ifdef NOVA_DEBUG
		{
			// Extensions
			extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

			// Layers
			layers.emplace_back("VK_LAYER_KHRONOS_validation");
		}
		#endif // NOVA_DEBUG

		vk::InstanceCreateInfo create_info{ {}, &app_info, layers, extensions };

		// Log Layers
		#if __N_OVA_BARK_STATE_DEBUG == 1
		log_enumerations();
		#endif // __N_OVA_BARK_STATE_DEBUG

		#if __N_OVA_BARK_STATE_INFO == 1
		nova_bark_info("Vulkan Extensions:");
		for (const auto& ext : extensions)
			nova_bark_info("\t{}", ext);
		nova_bark_info("Vulkan Validation Layers:");
		for (const auto& ext : layers)
			nova_bark_info("\t{}", ext);
		#endif // __N_OVA_BARK_STATE_INFO

		// Set pNext for debug handler
		#ifdef NOVA_DEBUG
		auto info = debug_info();
		create_info.pNext = &info;
		#endif // NOVA_DEBUG

		cxt.instance = vk::createInstance(create_info, cxt.alloc);
		nova_assert(cxt.instance, "Failed to Create VK Instance");

		#ifdef NOVA_DEBUG
		create_debugger(cxt);
		#endif // NOVA_DEBUG

	}

	void destroy_instance(const Context& cxt) {
		nvk_traced("Instance");

		#ifdef NOVA_DEBUG
		destroy_debugger(cxt);
		#endif // NOVA_DEBUG

		cxt.instance.destroy();
	}

}
#endif // NOVA_ABYSS_VULKAN
