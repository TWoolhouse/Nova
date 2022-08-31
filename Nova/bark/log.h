#pragma once
#include "meta/head.h"
#include "log_state.h"
#include <format>

#define __N_OVA_LOCATION CONCAT(__FILE__, CONCAT(":", STRINGIFY(__LINE__)))

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

	NOVAPI void submit(const Level level, const char* location, const std::string& msg);

	template<typename ...Args>
	void report(const Level level, const char* location, const std::string_view msg, Args&&... args) {
		return submit(level, location, std::vformat(msg, std::make_format_args(args...)));
	}

#ifdef nova_assert
	NOVAPI void assertion(bool condition, const std::string_view msg, const std::string_view file, const int line);
#endif // nova_assert
}

#define __n_ova_bark_log(level, message, ...) ::Nova::bark::report(::Nova::bark::Level::level, __N_OVA_LOCATION, message, ##__VA_ARGS__)

#define nova_bark_format(message, ...) std::vformat(message, std::make_format_args(##__VA_ARGS__))

#define nova_bark_fatal(message, ...) { __n_ova_bark_log(Fatal, message, ##__VA_ARGS__); NOVA_BREAKPOINT(); }
#define nova_bark_error(message, ...) __n_ova_bark_log(Error, message, ##__VA_ARGS__)

#if __N_OVA_BARK_STATE_WARN == 1
#define nova_bark_warn(message, ...) __n_ova_bark_log(Warn, message, ##__VA_ARGS__)
#else
#define nova_bark_warn(message, ...)
#endif // __N_OVA_BARK_STATE_WARN

#if __N_OVA_BARK_STATE_INIT == 1
#define nova_bark_init(message, ...) __n_ova_bark_log(Init, message, ##__VA_ARGS__)
#define nova_bark_term(message, ...) __n_ova_bark_log(Term, message, ##__VA_ARGS__)
#else
#define nova_bark_init(message, ...)
#define nova_bark_term(message, ...)
#endif // __N_OVA_BARK_STATE_INIT

#if __N_OVA_BARK_STATE_INFO == 1
#define nova_bark_info(message, ...) __n_ova_bark_log(Info, message, ##__VA_ARGS__)
#else
#define nova_bark_info(message, ...)
#endif // __N_OVA_BARK_STATE_INFO

#if __N_OVA_BARK_STATE_TRACE == 1
#define nova_bark_trace(message, ...) __n_ova_bark_log(Trace, message, ##__VA_ARGS__)
#else
#define nova_bark_trace(message, ...)
#endif // __N_OVA_BARK_STATE_TRACE

#if __N_OVA_BARK_STATE_DEBUG == 1
#define nova_bark_debug(message, ...) __n_ova_bark_log(Debug, message, ##__VA_ARGS__)
#else
#define nova_bark_debug(message, ...)
#endif // __N_OVA_BARK_STATE_DEBUG
