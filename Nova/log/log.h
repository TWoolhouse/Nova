#pragma once
#include "defines.h"
#include <format>

#define __N_OVA_BARK_STATE_WARN
#define __N_OVA_BARK_STATE_INFO
#define __N_OVA_BARK_STATE_DEBUG

#ifdef NOVA_RELEASE
#undef __N_OVA_BARK_STATE_DEBUG
#endif // NOVA_RELEASE

#ifdef NOVA_DEBUG
#define nova_assert(cond, msg) ::Nova::Bark::assertion(cond, msg, __FILE__, __LINE__)
#endif // NOVA_DEBUG

namespace Nova::Bark {
	enum class Level : char {
		Debug = 0,
		Info, Warn,
		Error, Fatal,

		MAX
	};

	NOVAPI void Initialize();
	NOVAPI void Terminate();

	NOVAPI void submit(const Level level, const std::string& msg);

	template<typename ...Args>
	void report(const Level level, const std::string_view msg, Args&&... args) {
		return submit(level, std::format(msg, args...));
	}

	#ifdef nova_assert
	NOVAPI void assertion(bool condition, const std::string_view msg, const std::string_view file, const int line);
	#endif // nova_assert
}

#define nova_bark_fatal(message, ...) ::Nova::Bark::report(::Nova::Bark::Level::Fatal, message, ##__VA_ARGS__); __debugbreak()
#define nova_bark_error(message, ...) ::Nova::Bark::report(::Nova::Bark::Level::Error, message, ##__VA_ARGS__)

#ifdef __N_OVA_BARK_STATE_WARN
#define nova_bark_warn(message, ...) ::Nova::Bark::report(::Nova::Bark::Level::Warn, message, ##__VA_ARGS__)
#else
#define nova_bark_warn(message, ...)
#endif // __N_OVA_BARK_STATE_WARN

#ifdef __N_OVA_BARK_STATE_INFO
#define nova_bark_info(message, ...) ::Nova::Bark::report(::Nova::Bark::Level::Info, message, ##__VA_ARGS__)
#else
#define nova_bark_info(message, ...)
#endif // __N_OVA_BARK_STATE_INFO

#ifdef __N_OVA_BARK_STATE_DEBUG
#define nova_bark_debug(message, ...) ::Nova::Bark::report(::Nova::Bark::Level::Debug, message, ##__VA_ARGS__)
#else
#define nova_bark_debug(message, ...)
#endif // __N_OVA_BARK_STATE_DEBUG
