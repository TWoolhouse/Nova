#pragma once
#include "meta/head.h"
#include "bark/bark.h"
#include "_vulkan.h"

#ifndef NOVA_ABYSS_DEBUG
#ifdef NOVA_DEBUG
#define NOVA_ABYSS_DEBUG 1
#endif // NOVA_DEBUG
#endif // !__N_OVA_ABYSS_DEBUG

#ifndef __N_OVA_BARK_ABYSS
#define __N_OVA_BARK_ABYSS 1
#endif // !__N_OVA_BARK_ABYSS

#ifndef __N_OVA_BARK_ABYSS_VERBOSE
#define __N_OVA_BARK_ABYSS_VERBOSE 0
#endif // !__N_OVA_BARK_ABYSS_VERBOSE

#ifdef NOVA_DEBUG
#define VK_CHECK(expr) nova_assert(expr == VK_SUCCESS, "VK Check Failed!")
#else // !NOVA_DEBUG
#define VK_CHECK(expr) expr
#endif // NOVA_DEBUG

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
			nova_bark_trace("[VKT] {} {}!", stmtf, msg);
		}
	};
}

#define nvk_trace(obj, stmtc, stmtf) ::Nova::abyss::vkn::__NVK_Trace CONCAT(__nvk_trace_, __COUNTER__){ obj, stmtc, stmtf }
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

namespace Nova::abyss::vkn {
	const cstr result_string(vk::Result result);
}

template<class CharT>
struct std::formatter<vk::Result, CharT> : std::formatter<std::underlying_type_t<vk::Result>, CharT> {
	template<class FormatContext>
	auto format(vk::Result _enum, FormatContext& fc) {
		return std::format_to(fc.out(), Nova::abyss::vkn::result_string(_enum));
	}
};