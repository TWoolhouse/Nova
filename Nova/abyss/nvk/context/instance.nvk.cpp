#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"
#include "instance.h"
#include "logger.h"
#include "surface.h"
#include "context.h"

#define VERSION_ARGS(version) \
VK_API_VERSION_VARIANT(version), \
VK_API_VERSION_MAJOR(version), \
VK_API_VERSION_MINOR(version), \
VK_API_VERSION_PATCH(version)

namespace Nova::abyss::nvk {

	inline auto vk_version_make(meta::version::Version version) {
		return VK_MAKE_API_VERSION(0, meta::version::major(version), meta::version::minor(version), meta::version::patch(version));
	}

	inline void log_available_layers_extensions() {
		if constexpr (Nova::bark::def::debug) {
			auto layers = vk::enumerateInstanceLayerProperties();
			nova_bark_debug("VK Availble Layers: {}", layers.size());
			for (const auto& layer : layers) {
				nova_bark_debug("\t: {}", layer.layerName);
			}

			auto extensions = vk::enumerateInstanceExtensionProperties();
			nova_bark_debug("VK Availble Extensions: {}", extensions.size());
			for (const auto& ext : extensions) {
				nova_bark_debug("\t: {}", ext.extensionName);
			}
		}
	}

	inline void log_requested_layers_extensions(const Setup& properties) {
		if constexpr (Nova::bark::def::info) {
			nova_bark_info("Vulkan Layers: {}", properties.layers.size());
			for (const auto& ext : properties.layers)
				nova_bark_info("\t{}", ext);

			nova_bark_info("Vulkan Extensions: {}", properties.extensions_instance.size());
			for (const auto& ext : properties.extensions_instance)
				nova_bark_info("\t{}", ext);
		}
	}

	Instance::Instance(const core::Information& info, const Setup& properties) :
		self(VK_NULL_HANDLE),
		#ifdef __N_OVA_ABYSS_DEBUG
		logger(VK_NULL_HANDLE),
		#endif // __N_OVA_ABYSS_DEBUG
		surface(VK_NULL_HANDLE)
	{
		nova_bark_init("VK Instance");

		vk::ApplicationInfo info_app{
			.pApplicationName = info.name.data(),
			.applicationVersion = vk_version_make(info.version),
			.pEngineName = meta::version::engine_name.data(),
			.engineVersion = vk_version_make(meta::version::engine),
			.apiVersion = VK_VERSION,
		};
		nova_bark_info("Vulkan: {}.{}.{}.{}", VERSION_ARGS(info_app.apiVersion));

		auto info_logger = Logger::info();
		vk::InstanceCreateInfo info_instance{
			.pNext = &info_logger,
			.pApplicationInfo = &info_app,
			.enabledLayerCount = static_cast<uint32_t>(properties.layers.size()),
			.ppEnabledLayerNames = properties.layers.data(),
			.enabledExtensionCount = static_cast<uint32_t>(properties.extensions_instance.size()),
			.ppEnabledExtensionNames = properties.extensions_instance.data(),
		};

		log_available_layers_extensions();
		log_requested_layers_extensions(properties);

		self = NVK_CHECK(vk::createInstance(info_instance, nova_abyss_api->alloc), "Failed to create VK Instance!");
		#ifdef __N_OVA_ABYSS_DEBUG
		this->logger = Logger::create(self);
		#endif // __N_OVA_ABYSS_DEBUG
		surface = Surface::create(self);
	}

	Instance::~Instance() {
		Surface::destroy(surface, self);
		#ifdef __N_OVA_ABYSS_DEBUG
		Logger::destroy(this->logger, self);
		#endif // __N_OVA_ABYSS_DEBUG
		nova_bark_term("VK Instance");
		self.destroy(nova_abyss_api->alloc);
	}

}

#endif // NOVA_ABYSS_VULKAN
