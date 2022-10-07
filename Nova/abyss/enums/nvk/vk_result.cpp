#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "vk.h"

nova_meta_enum_str(vk::Result, result) {
	switch (result) {
		case vk::Result::eSuccess:	return "Success";
		case vk::Result::eNotReady:	return "NotReady";
		case vk::Result::eTimeout:	return "Timeout";
		case vk::Result::eEventSet:	return "EventSet";
		case vk::Result::eEventReset:	return "EventReset";
		case vk::Result::eIncomplete:	return "Incomplete";
		case vk::Result::eErrorOutOfHostMemory:	return "ErrorOutOfHostMemory";
		case vk::Result::eErrorOutOfDeviceMemory:	return "ErrorOutOfDeviceMemory";
		case vk::Result::eErrorInitializationFailed:	return "ErrorInitializationFailed";
		case vk::Result::eErrorDeviceLost:	return "ErrorDeviceLost";
		case vk::Result::eErrorMemoryMapFailed:	return "ErrorMemoryMapFailed";
		case vk::Result::eErrorLayerNotPresent:	return "ErrorLayerNotPresent";
		case vk::Result::eErrorExtensionNotPresent:	return "ErrorExtensionNotPresent";
		case vk::Result::eErrorFeatureNotPresent:	return "ErrorFeatureNotPresent";
		case vk::Result::eErrorIncompatibleDriver:	return "ErrorIncompatibleDriver";
		case vk::Result::eErrorTooManyObjects:	return "ErrorTooManyObjects";
		case vk::Result::eErrorFormatNotSupported:	return "ErrorFormatNotSupported";
		case vk::Result::eErrorFragmentedPool:	return "ErrorFragmentedPool";
		case vk::Result::eErrorUnknown:	return "ErrorUnknown";
		case vk::Result::eErrorOutOfPoolMemory:	return "ErrorOutOfPoolMemory";
		case vk::Result::eErrorInvalidExternalHandle:	return "ErrorInvalidExternalHandle";
		case vk::Result::eErrorFragmentation:	return "ErrorFragmentation";
		case vk::Result::eErrorInvalidOpaqueCaptureAddress:	return "ErrorInvalidOpaqueCaptureAddress";
		case vk::Result::eErrorSurfaceLostKHR:	return "ErrorSurfaceLostKHR";
		case vk::Result::eErrorNativeWindowInUseKHR:	return "ErrorNativeWindowInUseKHR";
		case vk::Result::eSuboptimalKHR:	return "SuboptimalKHR";
		case vk::Result::eErrorOutOfDateKHR:	return "ErrorOutOfDateKHR";
		case vk::Result::eErrorIncompatibleDisplayKHR:	return "ErrorIncompatibleDisplayKHR";
		case vk::Result::eErrorValidationFailedEXT:	return "ErrorValidationFailedEXT";
		case vk::Result::eErrorInvalidShaderNV:	return "ErrorInvalidShaderNV";
		case vk::Result::eErrorInvalidDrmFormatModifierPlaneLayoutEXT:	return "ErrorInvalidDrmFormatModifierPlaneLayoutEXT";
		case vk::Result::eErrorNotPermittedEXT:	return "ErrorNotPermittedEXT";
		case vk::Result::eThreadIdleKHR:	return "ThreadIdleKHR";
		case vk::Result::eThreadDoneKHR:	return "ThreadDoneKHR";
		case vk::Result::eOperationDeferredKHR:	return "OperationDeferredKHR";
		case vk::Result::eOperationNotDeferredKHR:	return "OperationNotDeferredKHR";
		case vk::Result::ePipelineCompileRequiredEXT:	return "PipelineCompileRequiredEXT";
		// case vk::Result::eErrorFragmentationEXT:	return "ErrorFragmentationEXT";
		// case vk::Result::eErrorInvalidDeviceAddressEXT:	return "ErrorInvalidDeviceAddressEXT";
		// case vk::Result::eErrorInvalidExternalHandleKHR:	return "ErrorInvalidExternalHandleKHR";
		// case vk::Result::eErrorInvalidOpaqueCaptureAddressKHR:	return "ErrorInvalidOpaqueCaptureAddressKHR";
		// case vk::Result::eErrorOutOfPoolMemoryKHR:	return "ErrorOutOfPoolMemoryKHR";
		// case vk::Result::eErrorPipelineCompileRequiredEXT:	return "ErrorPipelineCompileRequiredEXT";
		default:
			nova_bark_warn("Unknown Case [vk Result]: {}", cpp::to_underlying(result));
			return "Unknown Error";
	}
}

#endif // NOVA_ABYSS_VULKAN
