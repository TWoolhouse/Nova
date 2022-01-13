#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "debug.h"

PFN_vkCreateDebugUtilsMessengerEXT create_debug_messenger;
PFN_vkDestroyDebugUtilsMessengerEXT destroy_debug_messenger;

inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(
	VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugUtilsMessengerEXT* pMessenger)
{
	return create_debug_messenger(instance, pCreateInfo, pAllocator, pMessenger);
}
inline VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(
	VkInstance instance,
	VkDebugUtilsMessengerEXT messenger,
	VkAllocationCallbacks const* pAllocator)
{
	return destroy_debug_messenger(instance, messenger, pAllocator);
}

namespace Nova::abyss::vkn {

	vk::DebugUtilsMessengerEXT debugger;

	VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageTypes,
		VkDebugUtilsMessengerCallbackDataEXT const* pCallbackData,
		void* /*pUserData*/)
	{
		static constexpr auto header = "[Vk] {}"sv;
		switch (static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(messageSeverity)) {
		case (vk::DebugUtilsMessageSeverityFlagBitsEXT::eError):
			nova_bark_error(header, pCallbackData->pMessage);
			break;
		case (vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning):
			nova_bark_warn(header, pCallbackData->pMessage);
			break;
		case (vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo):
			nova_bark_info(header, pCallbackData->pMessage);
			break;
		case (vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose):
			nova_bark_trace(header, pCallbackData->pMessage);
			break;
		default:
			nova_bark_debug(header, pCallbackData->pMessage);
			break;
		}

		return VK_FALSE;
	}

	vk::DebugUtilsMessengerCreateInfoEXT debug_info() {
		constexpr auto log_severity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
			| vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
			//| vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo
			//| vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
			; // log_serevrity
		constexpr auto message_types = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
			| vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
			| vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
			; // message_types

		return {
			{}, log_severity, message_types, debug_callback
		};
	}

	void create_debugger(const Context& cxt) {
		nvk_tracec(Creating, "Debugger");
		create_debug_messenger =
			reinterpret_cast<decltype(create_debug_messenger)>(cxt.instance.getProcAddr("vkCreateDebugUtilsMessengerEXT"));
		nova_assert(create_debug_messenger, "Unable to find function: vkCreateDebugUtilsMessengerEXT");

		destroy_debug_messenger =
			reinterpret_cast<decltype(destroy_debug_messenger)>(cxt.instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT"));
		nova_assert(destroy_debug_messenger, "Unable to find function: vkDestroyDebugUtilsMessengerEXT");

		debugger = cxt.instance.createDebugUtilsMessengerEXT(debug_info(), cxt.alloc);
		nvk_tracef(Created, "Debugger");
	}

	void destroy_debugger(const Context& cxt) {
		cxt.instance.destroyDebugUtilsMessengerEXT(debugger, cxt.alloc);
	}

}
#endif // NOVA_ABYSS_VULKAN
