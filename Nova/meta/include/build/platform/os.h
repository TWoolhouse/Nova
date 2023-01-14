#pragma once

// Find the OS

namespace Nova::meta::def {

	enum class OS : uint8_t {
		Windows,
	}; // TODO add constexpr variable

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
// Windows
#define NOVA_OS_WINDOWS
constexpr auto os = OS::Windows;
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
	// Linux OS
#define NOVA_OS_LINUX
#if defined(__ANDROID__)
#define NOVA_OS_ANDROID
#endif
#elif defined(__unix__)
	// Unix
#define NOVA_OS_UNIX
#elif defined(_POSIX_VERSION)
	// Posix
#define NOVA_OS_POSIX
#elif defined(__APPLE__)
	// Apple platforms
#define NOVA_OS_APPLE
#include <TargetConditionals.h>
#if defined(TARGET_IPHONE_SIMULATOR)
// iOS Simulator
#define NOVA_OS_IOS
#define NOVA_OS_IOS_SIMULATOR
#elif defined(TARGET_OS_IPHONE)
#define NOVA_OS_IOS
// iOS device
#elif defined(TARGET_OS_MAC)
// Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif
#else
	// Error
#error "Unknown platform!"
#endif

}
