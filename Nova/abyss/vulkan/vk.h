#pragma once
#include "meta/head.h"
#include "bark/bark.h"
#include "_vulkan.h"

#ifndef __N_OVA_BARK_ABYSS
#define __N_OVA_BARK_ABYSS 1
#endif // !__N_OVA_BARK_ABYSS

#ifndef __N_OVA_BARK_ABYSS_VERBOSE
#define __N_OVA_BARK_ABYSS_VERBOSE 0
#endif // !__N_OVA_BARK_ABYSS_VERBOSE

#if __N_OVA_BARK_ABYSS == 1 && __N_OVA_BARK_STATE_TRACE == 1
#if __N_OVA_BARK_ABYSS_VERBOSE == 1
namespace Nova::abyss::vkn {
	struct __NVK_Trace {
		const std::string_view msg, stmtc, stmtf;
		__NVK_Trace(const std::string_view& msg,
			const std::string_view& stmtc, const std::string_view& stmtf) : msg(msg), stmtc(stmtc), stmtf(stmtf) {
			nova_bark_trace("[VKT] {} {}", stmtc, msg);
		}
		~__NVK_Trace() {
			nova_bark_trace("[VKT] {} {}!", msg, stmtf);
		}
	};
}

#define nvk_trace(obj, stmtc, stmtf) __NVK_Trace CONCAT(__nvk_trace_, __COUNTER__){ obj, stmtc, stmtf }
#else // !__N_OVA_BARK_ABYSS_VERBOSE
#define nvk_trace(obj, stmtc, stmtf) nova_bark_trace("[VKT] {} {}", stmtc, obj)
#endif // __N_OVA_BARK_ABYSS_VERBOSE
#define nvk_tracec(obj) nvk_trace(obj, "Creating"sv, "Created"sv)
#define nvk_traced(obj) nvk_trace(obj, "Destroying"sv, "Destroyed"sv)

#else
#define nvk_trace(obj, stmtc, stmtf)
#define nvk_tracec(obj)
#define nvk_traced(obj)
#endif // __N_OVA_BARK_STATE_TRACE 