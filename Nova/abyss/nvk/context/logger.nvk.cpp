#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"
#include "logger.h"
#include "context.h"

inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(
	VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugUtilsMessengerEXT* pMessenger) {
	return reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"))(
		instance, pCreateInfo, pAllocator, pMessenger
	);
}
inline VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(
	VkInstance instance,
	VkDebugUtilsMessengerEXT messenger,
	VkAllocationCallbacks const* pAllocator) {
	return reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"))(
		instance, messenger, pAllocator
	);
}

namespace Nova::abyss::nvk::Logger {

	vk::DebugUtilsMessengerEXT create(vk::Instance& instance) {
		nova_bark_init("VK Logger");
		return instance.createDebugUtilsMessengerEXT(info(), nova_abyss_api->alloc);
	}

	void destroy(vk::DebugUtilsMessengerEXT& logger, vk::Instance& instance) {
		nova_bark_term("VK Logger");
		instance.destroyDebugUtilsMessengerEXT(logger, nova_abyss_api->alloc);
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL log_callback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageTypes,
		VkDebugUtilsMessengerCallbackDataEXT const* pCallbackData,
		void* /*pUserData*/
	) {
		// TODO: Change messaged based on the message type.
		static constexpr auto header = "[VK] {}"sv;
		switch (static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(messageSeverity)) {
			case (vk::DebugUtilsMessageSeverityFlagBitsEXT::eError):
				nova_bark_error(header, pCallbackData->pMessage);
				break;
			case (vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning):
				nova_bark_warn(header, pCallbackData->pMessage);
				break;
			case (vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo):
				nova_bark_trace(header, pCallbackData->pMessage);
				break;
			case (vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose):
				nova_bark_debug(header, pCallbackData->pMessage);
				break;
			default:
				nova_bark_trace(header, pCallbackData->pMessage);
				break;
		}
		return VK_FALSE;
	}

	constexpr vk::DebugUtilsMessengerCreateInfoEXT info() {
		// TODO: Change which message types are available from defines / config
		constexpr auto log_severity = vk::DebugUtilsMessageSeverityFlagBitsEXT{ 0 }
			#ifdef __N_OVA_ABYSS_BARK_ERROR
				| vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
			#endif // __N_OVA_ABYSS_BARK_ERROR
			#ifdef __N_OVA_ABYSS_BARK_WARN
				| vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
			#endif // __N_OVA_ABYSS_BARK_WARN
			#ifdef __N_OVA_ABYSS_BARK_INFO
				| vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo
			#endif // __N_OVA_ABYSS_BARK_INFO
			#ifdef __N_OVA_ABYSS_BARK_DEBUG
				| vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
			#endif // __N_OVA_ABYSS_BARK_DEBUG
			; // log_severity
		constexpr auto message_types = vk::DebugUtilsMessageTypeFlagBitsEXT{ 0 }
			| vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
			| vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
			| vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
			; // message_types

		return vk::DebugUtilsMessengerCreateInfoEXT{
			.messageSeverity = log_severity,
			.messageType = message_types,
			.pfnUserCallback = log_callback,
		};
	}

}

#endif // NOVA_ABYSS_VULKAN
