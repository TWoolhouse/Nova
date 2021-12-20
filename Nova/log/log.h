#pragma once
#include "defines.h"
#include <initializer_list>

#define NOVA_BARK_STATE_WARN
#define NOVA_BARK_STATE_INFO
#define NOVA_BARK_STATE_DEBUG

#ifdef NOVA_RELEASE
#undef NOVA_BARK_STATE_DEBUG
#endif

#include <format>

namespace Nova::Bark {
	enum class Level : char {
		Debug = 0,
		Info, Warn,
		Error, Fatal,

		MAX
	};

	NOVAPI void Initialize();
	NOVAPI void Terminate();

	NOVAPI void submit(Level level, const std::string& msg);

	template<typename ...Args>
	void report(Level level, std::string_view msg, Args&&... args) {
		return submit(level, std::format(msg, args...));
	}
}

#define NOVA_BARK_FATAL(message, ...) ::Nova::Bark::report(::Nova::Bark::Level::Fatal, message, ##__VA_ARGS__)
#define NOVA_BARK_ERROR(message, ...) ::Nova::Bark::report(::Nova::Bark::Level::Error, message, ##__VA_ARGS__)

#ifdef NOVA_BARK_STATE_WARN
#define NOVA_BARK_WARN(message, ...) ::Nova::Bark::report(::Nova::Bark::Level::Warn, message, ##__VA_ARGS__)
#else
#define NOVA_BARK_WARN(message, ...)
#endif

#ifdef NOVA_BARK_STATE_WARN
#define NOVA_BARK_INFO(message, ...) ::Nova::Bark::report(::Nova::Bark::Level::Info, message, ##__VA_ARGS__)
#else
#define NOVA_BARK_INFO(message, ...)
#endif

#ifdef NOVA_BARK_STATE_WARN
#define NOVA_BARK_DEBUG(message, ...) ::Nova::Bark::report(::Nova::Bark::Level::Debug, message, ##__VA_ARGS__)
#else
#define NOVA_BARK_DEBUG(message, ...)
#endif
