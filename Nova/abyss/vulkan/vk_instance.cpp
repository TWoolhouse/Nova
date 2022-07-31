#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "context.h"
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

	void Context::create_instance(const std::string_view& name) {
		nvk_tracec("Instance");

		vk::ApplicationInfo app_info{
			.pApplicationName = name.data(),
			.applicationVersion = VK_MAKE_API_VERSION(0, 0, 1, 0),
			.pEngineName = engine_name.data(),
			.engineVersion = VK_MAKE_API_VERSION(0, 0, 1, 0),
			.apiVersion = VK_API_VERSION_1_2,
		};

		std::vector<cstr> layers{};
		std::vector<cstr> extensions{
			VK_KHR_SURFACE_EXTENSION_NAME
		};

		platform_extensions(extensions);

		// Debug Extensions & Layers
	#if NOVA_ABYSS_DEBUG == 1
		{
			// Extensions
			extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

			// Layers
			layers.emplace_back("VK_LAYER_KHRONOS_validation");
		}
	#endif // NOVA_ABYSS_DEBUG

		vk::InstanceCreateInfo create_info{
			.pApplicationInfo = &app_info,
			.enabledLayerCount = static_cast<uint32_t>(layers.size()),
			.ppEnabledLayerNames = layers.data(),
			.enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
			.ppEnabledExtensionNames = extensions.data(),
		};

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
	#if NOVA_ABYSS_DEBUG == 1
		auto info = debug_info();
		create_info.pNext = &info;
	#endif // NOVA_ABYSS_DEBUG

		instance = vk::createInstance(create_info, alloc);
		nova_assert(instance, "Failed to Create VK Instance");

	#if NOVA_ABYSS_DEBUG == 1
		create_debugger(*this);
	#endif // NOVA_ABYSS_DEBUG
	}

	void Context::destroy_instance() {
		nvk_traced("Instance");

	#if NOVA_ABYSS_DEBUG == 1
		destroy_debugger(*this);
	#endif // NOVA_ABYSS_DEBUG

		instance.destroy();
	}

}
#endif // NOVA_ABYSS_VULKAN
