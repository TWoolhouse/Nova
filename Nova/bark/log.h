#pragma once
#include "meta/head.h"
#include <format>

#ifndef __N_OVA_BARK_STATE_WARN
#define __N_OVA_BARK_STATE_WARN 1
#endif // !__N_OVA_BARK_STATE_WARN

#ifndef __N_OVA_BARK_STATE_INIT
#define __N_OVA_BARK_STATE_INIT 1
#endif // !__N_OVA_BARK_STATE_INIT

#ifndef __N_OVA_BARK_STATE_INFO
#define __N_OVA_BARK_STATE_INFO 1
#endif // !__N_OVA_BARK_STATE_INFO

#ifndef __N_OVA_BARK_STATE_TRACE
#ifdef NOVA_DEBUG
#define __N_OVA_BARK_STATE_TRACE 1
#endif // NOVA_DEBUG
#endif // !__N_OVA_BARK_STATE_TRACE

#ifndef __N_OVA_BARK_STATE_DEBUG
#ifdef NOVA_DEBUG
#define __N_OVA_BARK_STATE_DEBUG 1
#endif // NOVA_DEBUG
#endif // !__N_OVA_BARK_STATE_DEBUG



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

#if __N_OVA_BARK_STATE_WARN == 1
#define nova_bark_warn(message, ...) ::Nova::bark::report(::Nova::bark::Level::Warn, message, ##__VA_ARGS__)
#else
#define nova_bark_warn(message, ...)
#endif // __N_OVA_BARK_STATE_WARN

#if __N_OVA_BARK_STATE_INIT == 1
#define nova_bark_init(message, ...) ::Nova::bark::report(::Nova::bark::Level::Init, message, ##__VA_ARGS__)
#define nova_bark_term(message, ...) ::Nova::bark::report(::Nova::bark::Level::Term, message, ##__VA_ARGS__)
#else
#define nova_bark_init(message, ...)
#define nova_bark_term(message, ...)
#endif // __N_OVA_BARK_STATE_INIT

#if __N_OVA_BARK_STATE_INFO == 1
#define nova_bark_info(message, ...) ::Nova::bark::report(::Nova::bark::Level::Info, message, ##__VA_ARGS__)
#else
#define nova_bark_info(message, ...)
#endif // __N_OVA_BARK_STATE_INFO

#if __N_OVA_BARK_STATE_TRACE == 1
#define nova_bark_trace(message, ...) ::Nova::bark::report(::Nova::bark::Level::Trace, message, ##__VA_ARGS__)
#else
#define nova_bark_trace(message, ...)
#endif // __N_OVA_BARK_STATE_TRACE

#if __N_OVA_BARK_STATE_DEBUG == 1
#define nova_bark_debug(message, ...) ::Nova::bark::report(::Nova::bark::Level::Debug, message, ##__VA_ARGS__)
#else
#define nova_bark_debug(message, ...)
#endif // __N_OVA_BARK_STATE_DEBUG
