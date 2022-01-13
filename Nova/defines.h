#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define NOVA_OS_WINDOWS
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
// Catch anything not caught by the above.
#define NOVA_OS_UNIX
#elif defined(_POSIX_VERSION)
// Posix
#define NOVA_OS_POSIX
#elif __APPLE__
// Apple platforms
#define NOVA_OS_APPLE
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#define NOVA_OS_IOS
#define NOVA_OS_IOS_SIMULATOR
#elif TARGET_OS_IPHONE
#define NOVA_OS_IOS
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif
#else
#error "Unknown platform!"
#endif

#ifdef NOVA_EXPORT
#define NOVAPI __declspec(dllexport)
#else
#define NOVAPI __declspec(dllimport)
#endif

#ifdef DEBUG
#define NOVA_DEBUG
#else
#define NOVA_RELEASE
#endif

#define NODISCARD [[nodiscard]]

#define formatter_enum(EnumName) \
template<class CharT> \
struct std::formatter<EnumName, CharT> : std::formatter<std::underlying_type_t<EnumName>, CharT> { \
	template<class FormatContext> \
	auto format(EnumName _enum, FormatContext& fc) { \
		return std::formatter<std::underlying_type_t<EnumName>, CharT>::format(static_cast<std::underlying_type_t<EnumName>>(_enum), fc); \
	} \
}

namespace Nova {}

#include <type_traits>
#include <concepts>

#include <string>
#include <string_view>

#include <exception>
#include <functional>

#include <ranges>
#include <array>
#include <deque>
#include <set>
#include <bitset>

using cstr = const char*;
using namespace std::string_view_literals;
