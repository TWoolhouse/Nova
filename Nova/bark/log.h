#pragma once
#include "meta/head.h"
#include <format>

#define __N_OVA_BARK_STATE_WARN
#define __N_OVA_BARK_STATE_INIT
#define __N_OVA_BARK_STATE_INFO
#define __N_OVA_BARK_STATE_TRACE
#define __N_OVA_BARK_STATE_DEBUG

#ifdef NOVA_RELEASE
#undef __N_OVA_BARK_STATE_TRACE
#undef __N_OVA_BARK_STATE_DEBUG
#endif // NOVA_RELEASE

#ifdef NOVA_DEBUG
#define nova_assert(cond, msg) ::Nova::bark::assertion(cond, msg, __FILE__, __LINE__)
#else // !NOVA_DEBUG
#define nova_assert(cond, msg)
#endif // NOVA_DEBUG

namespace Nova::bark {
	enum class Level : char {
		Debug = 0,
		Trace,
		Info, Init, Term,
		Warn,
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

#define nova_bark_fatal(message, ...) ::Nova::bark::report(::Nova::bark::Level::Fatal, message, ##__VA_ARGS__); __debugbreak()
#define nova_bark_error(message, ...) ::Nova::bark::report(::Nova::bark::Level::Error, message, ##__VA_ARGS__)

#ifdef __N_OVA_BARK_STATE_WARN
#define nova_bark_warn(message, ...) ::Nova::bark::report(::Nova::bark::Level::Warn, message, ##__VA_ARGS__)
#else
#define nova_bark_warn(message, ...)
#endif // __N_OVA_BARK_STATE_WARN

#ifdef __N_OVA_BARK_STATE_INIT
#define nova_bark_init(message, ...) ::Nova::bark::report(::Nova::bark::Level::Init, message, ##__VA_ARGS__)
#define nova_bark_term(message, ...) ::Nova::bark::report(::Nova::bark::Level::Term, message, ##__VA_ARGS__)
#else
#define nova_bark_init(message, ...)
#define nova_bark_term(message, ...)
#endif // __N_OVA_BARK_STATE_INIT

#ifdef __N_OVA_BARK_STATE_INFO
#define nova_bark_info(message, ...) ::Nova::bark::report(::Nova::bark::Level::Info, message, ##__VA_ARGS__)
#else
#define nova_bark_info(message, ...)
#endif // __N_OVA_BARK_STATE_INFO

#ifdef __N_OVA_BARK_STATE_TRACE
#define nova_bark_trace(message, ...) ::Nova::bark::report(::Nova::bark::Level::Trace, message, ##__VA_ARGS__)
#else
#define nova_bark_trace(message, ...)
#endif // __N_OVA_BARK_STATE_TRACE

#ifdef __N_OVA_BARK_STATE_DEBUG
#define nova_bark_debug(message, ...) ::Nova::bark::report(::Nova::bark::Level::Debug, message, ##__VA_ARGS__)
#else
#define nova_bark_debug(message, ...)
#endif // __N_OVA_BARK_STATE_DEBUG
