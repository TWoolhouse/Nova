#pragma once
#include "meta/head.h"

namespace Nova::bark::def {

constexpr auto debug =
#ifndef __N_OVA_BARK_STATE_DEBUG
#ifdef NOVA_DEBUG
#define __N_OVA_BARK_STATE_DEBUG 1
true;
#else // !NOVA_DEBUG
false;
#endif // NOVA_DEBUG
#else // __N_OVA_BARK_STATE_DEBUG
false;
#endif // !__N_OVA_BARK_STATE_DEBUG

constexpr auto trace =
#ifndef __N_OVA_BARK_STATE_TRACE
#ifdef NOVA_DEBUG
#define __N_OVA_BARK_STATE_TRACE 1
true;
#else // !NOVA_DEBUG
false;
#endif // NOVA_DEBUG
#else // __N_OVA_BARK_STATE_DEBUG
false;
#endif // !__N_OVA_BARK_STATE_TRACE

constexpr auto info =
#ifndef __N_OVA_BARK_STATE_INFO
#define __N_OVA_BARK_STATE_INFO 1
true;
#else // __N_OVA_BARK_STATE_DEBUG
false;
#endif // !__N_OVA_BARK_STATE_INFO

constexpr auto init =
#ifndef __N_OVA_BARK_STATE_INIT
#define __N_OVA_BARK_STATE_INIT 1
true;
#else // __N_OVA_BARK_STATE_DEBUG
false;
#endif // !__N_OVA_BARK_STATE_INIT

constexpr auto warn =
#ifndef __N_OVA_BARK_STATE_WARN
#define __N_OVA_BARK_STATE_WARN 1
true;
#else // __N_OVA_BARK_STATE_DEBUG
false;
#endif // !__N_OVA_BARK_STATE_WARN

constexpr auto error = true;
constexpr auto fatal = true;

}
