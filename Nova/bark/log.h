#pragma once
#include "meta/head.h"
#include "config.h"
#include "location.h"
#include <format>

#define nova_bark_format(message, ...) std::vformat(message, std::make_format_args(##__VA_ARGS__))

namespace Nova::bark {
	enum class Level : char {
		Fatal, Error,
		Warn,
		Todo,
		Info, Init, Term,
		Trace,
		Debug,
		Temporary,

		MAX
	};

	NOVAPI void Initialize();
	NOVAPI void Terminate();

	NOVAPI void submit(const Level level, const Location& location, const std::string& msg);

	template<typename ...Args>
	void report(const Level level, const Location location, const std::string_view msg, Args&&... args) {
		return submit(level, location, nova_bark_format(msg, args...));
	}

} // namespace Nova::bark

#define __n_ova_bark_log(level, message, ...) ::Nova::bark::report(::Nova::bark::Level::level, ::Nova::bark::Location::current(), message, ##__VA_ARGS__)

#ifdef __N_OVA_BARK_FATAL
#define nova_bark_fatal(message, ...) { __n_ova_bark_log(Fatal, message, ##__VA_ARGS__); NOVA_BREAKPOINT(); }
#else
#define nova_bark_fatal(message, ...)
#endif // __N_OVA_BARK_FATAL

#ifdef __N_OVA_BARK_ERROR
#define nova_bark_error(message, ...) __n_ova_bark_log(Error, message, ##__VA_ARGS__)
#else
#define nova_bark_error(message, ...)
#endif // __N_OVA_BARK_ERROR

#ifdef __N_OVA_BARK_WARN
#define nova_bark_warn(message, ...) __n_ova_bark_log(Warn, message, ##__VA_ARGS__)
#else
#define nova_bark_warn(message, ...)
#endif // __N_OVA_BARK_WARN

#ifdef __N_OVA_BARK_INIT
#define nova_bark_init(message, ...) __n_ova_bark_log(Init, message, ##__VA_ARGS__)
#define nova_bark_term(message, ...) __n_ova_bark_log(Term, message, ##__VA_ARGS__)
#else
#define nova_bark_init(message, ...)
#define nova_bark_term(message, ...)
#endif // __N_OVA_BARK_INIT

#ifdef __N_OVA_BARK_INFO
#define nova_bark_info(message, ...) __n_ova_bark_log(Info, message, ##__VA_ARGS__)
#else
#define nova_bark_info(message, ...)
#endif // __N_OVA_BARK_INFO

#ifdef __N_OVA_BARK_TRACE
#define nova_bark_trace(message, ...) __n_ova_bark_log(Trace, message, ##__VA_ARGS__)
#else
#define nova_bark_trace(message, ...)
#endif // __N_OVA_BARK_TRACE

#ifdef __N_OVA_BARK_DEBUG
#define nova_bark_debug(message, ...) __n_ova_bark_log(Debug, message, ##__VA_ARGS__)
#else
#define nova_bark_debug(message, ...)
#endif // __N_OVA_BARK_DEBUG

#ifdef __N_OVA_BARK_TODO
#define nova_bark_todo(message, ...) __n_ova_bark_log(Todo, message, ##__VA_ARGS__)
#else
#define nova_bark_todo(message, ...)
#endif // __N_OVA_BARK_TODO

#ifdef __N_OVA_BARK_UNIMPLEMENTED
#define nova_bark_unimplemented(message, ...) { __n_ova_bark_log(Todo, message, ##__VA_ARGS__); NOVA_BREAKPOINT(); }
#else
#define nova_bark_unimplemented(message, ...)
#endif // __N_OVA_BARK_UNIMPLEMENTED

#ifdef __N_OVA_BARK_TEMP
#define nova_bark_temp(message, ...) __n_ova_bark_log(Temporary, message, ##__VA_ARGS__)
#else
#define nova_bark_temp(message, ...)
#endif // __N_OVA_BARK_TEMP
