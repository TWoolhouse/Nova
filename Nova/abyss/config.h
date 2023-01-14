#pragma once
#include "meta/include/defines.h"

namespace Nova::abyss::def {

//-----------------------------------------------------------------//
//-----------------------__N_OVA_ABYSS_DEBUG-----------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_ABYSS_DEBUG

#if !defined(__N_OVA_ABYSS_DEBUG)
	#define __N_OVA_ABYSS_DEBUG
#elif __N_OVA_ABYSS_DEBUG == 0
	#undef __N_OVA_ABYSS_DEBUG
#endif // __N_OVA_ABYSS_DEBUG

constexpr bool debug =
#ifdef __N_OVA_ABYSS_DEBUG
	true
#else // !__N_OVA_ABYSS_DEBUG
	false
#endif // __N_OVA_ABYSS_DEBUG
;
#pragma endregion

//-----------------------------------------------------------------//
//-----------------------__N_OVA_ABYSS_CHECK-----------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_ABYSS_CHECK

#if !defined(__N_OVA_ABYSS_CHECK)
	#define __N_OVA_ABYSS_CHECK
#elif __N_OVA_ABYSS_CHECK == 0
	#undef __N_OVA_ABYSS_CHECK
#endif // __N_OVA_ABYSS_CHECK

constexpr bool check =
#ifdef __N_OVA_ABYSS_CHECK
	true
#else // !__N_OVA_ABYSS_CHECK
	false
#endif // __N_OVA_ABYSS_CHECK
;
#pragma endregion

namespace bark {

//-----------------------------------------------------------------//
//--------------------__N_OVA_ABYSS_BARK_ERROR---------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_ABYSS_BARK_ERROR

constexpr bool error = true;
#define __N_OVA_ABYSS_BARK_ERROR

#pragma endregion

//-----------------------------------------------------------------//
//---------------------__N_OVA_ABYSS_BARK_WARN---------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_ABYSS_BARK_WARN

#if !defined(__N_OVA_ABYSS_BARK_WARN)
	#define __N_OVA_ABYSS_BARK_WARN
#elif __N_OVA_ABYSS_BARK_WARN == 0
	#undef __N_OVA_ABYSS_BARK_WARN
#endif // __N_OVA_ABYSS_BARK_WARN

constexpr bool warn =
#ifdef __N_OVA_ABYSS_BARK_WARN
	true
#else // !__N_OVA_ABYSS_BARK_WARN
	false
#endif // __N_OVA_ABYSS_BARK_WARN
;
#pragma endregion

//-----------------------------------------------------------------//
//---------------------__N_OVA_ABYSS_BARK_INFO---------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_ABYSS_BARK_INFO

#if !defined(__N_OVA_ABYSS_BARK_INFO)
	#define __N_OVA_ABYSS_BARK_INFO
#elif __N_OVA_ABYSS_BARK_INFO == 0
	#undef __N_OVA_ABYSS_BARK_INFO
#endif // __N_OVA_ABYSS_BARK_INFO

constexpr bool info =
#ifdef __N_OVA_ABYSS_BARK_INFO
	true
#else // !__N_OVA_ABYSS_BARK_INFO
	false
#endif // __N_OVA_ABYSS_BARK_INFO
;
#pragma endregion

//-----------------------------------------------------------------//
//--------------------__N_OVA_ABYSS_BARK_DEBUG---------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_ABYSS_BARK_DEBUG

#if !defined(__N_OVA_ABYSS_BARK_DEBUG)
	#define __N_OVA_ABYSS_BARK_DEBUG
#elif __N_OVA_ABYSS_BARK_DEBUG == 0
	#undef __N_OVA_ABYSS_BARK_DEBUG
#endif // __N_OVA_ABYSS_BARK_DEBUG

constexpr bool debug =
#ifdef __N_OVA_ABYSS_BARK_DEBUG
	true
#else // !__N_OVA_ABYSS_BARK_DEBUG
	false
#endif // __N_OVA_ABYSS_BARK_DEBUG
;
#pragma endregion

} // namespace bark

} // namspace Nova::abyss::def
