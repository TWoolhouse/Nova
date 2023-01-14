#pragma once
#include "meta/include/defines.h"

namespace Nova::bark::def {

//-----------------------------------------------------------------//
//-----------------------__N_OVA_BARK_ASSERT-----------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_BARK_ASSERT

#if !defined(__N_OVA_BARK_ASSERT)
	#define __N_OVA_BARK_ASSERT
#elif __N_OVA_BARK_ASSERT == 0
	#undef __N_OVA_BARK_ASSERT
#endif // __N_OVA_BARK_ASSERT

constexpr bool assert =
#ifdef __N_OVA_BARK_ASSERT
	true
#else // !__N_OVA_BARK_ASSERT
	false
#endif // __N_OVA_BARK_ASSERT
;
#pragma endregion

//-----------------------------------------------------------------//
//----------------------__N_OVA_BARK_CONSOLE-----------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_BARK_CONSOLE

#if !defined(__N_OVA_BARK_CONSOLE)
	#define __N_OVA_BARK_CONSOLE
#elif __N_OVA_BARK_CONSOLE == 0
	#undef __N_OVA_BARK_CONSOLE
#endif // __N_OVA_BARK_CONSOLE

constexpr bool console =
#ifdef __N_OVA_BARK_CONSOLE
	true
#else // !__N_OVA_BARK_CONSOLE
	false
#endif // __N_OVA_BARK_CONSOLE
;
#pragma endregion

//-----------------------------------------------------------------//
//------------------------__N_OVA_BARK_FILE------------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_BARK_FILE

#if !defined(__N_OVA_BARK_FILE)
	#define __N_OVA_BARK_FILE
#elif __N_OVA_BARK_FILE == 0
	#undef __N_OVA_BARK_FILE
#endif // __N_OVA_BARK_FILE

constexpr bool file =
#ifdef __N_OVA_BARK_FILE
	true
#else // !__N_OVA_BARK_FILE
	false
#endif // __N_OVA_BARK_FILE
;
#pragma endregion

//-----------------------------------------------------------------//
//-----------------------__N_OVA_BARK_FATAL------------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_BARK_FATAL
constexpr bool fatal = true;
#define __N_OVA_BARK_FATAL
#pragma endregion

//-----------------------------------------------------------------//
//-----------------------__N_OVA_BARK_ERROR------------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_BARK_ERROR
constexpr bool error = true;
#define __N_OVA_BARK_ERROR
#pragma endregion

//-----------------------------------------------------------------//
//------------------------__N_OVA_BARK_WARN------------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_BARK_WARN

#if !defined(__N_OVA_BARK_WARN)
	#define __N_OVA_BARK_WARN
#elif __N_OVA_BARK_WARN == 0
	#undef __N_OVA_BARK_WARN
#endif // __N_OVA_BARK_WARN

constexpr bool warn =
#ifdef __N_OVA_BARK_WARN
	true
#else // !__N_OVA_BARK_WARN
	false
#endif // __N_OVA_BARK_WARN
;
#pragma endregion

//-----------------------------------------------------------------//
//------------------------__N_OVA_BARK_INIT------------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_BARK_INIT

#if !defined(__N_OVA_BARK_INIT)
	#define __N_OVA_BARK_INIT
#elif __N_OVA_BARK_INIT == 0
	#undef __N_OVA_BARK_INIT
#endif // __N_OVA_BARK_INIT

constexpr bool init =
#ifdef __N_OVA_BARK_INIT
	true
#else // !__N_OVA_BARK_INIT
	false
#endif // __N_OVA_BARK_INIT
;
#pragma endregion

//-----------------------------------------------------------------//
//------------------------__N_OVA_BARK_INFO------------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_BARK_INFO

#if !defined(__N_OVA_BARK_INFO)
	#define __N_OVA_BARK_INFO
#elif __N_OVA_BARK_INFO == 0
	#undef __N_OVA_BARK_INFO
#endif // __N_OVA_BARK_INFO

constexpr bool info =
#ifdef __N_OVA_BARK_INFO
	true
#else // !__N_OVA_BARK_INFO
	false
#endif // __N_OVA_BARK_INFO
;
#pragma endregion

//-----------------------------------------------------------------//
//-----------------------__N_OVA_BARK_TRACE------------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_BARK_TRACE

#if !defined(__N_OVA_BARK_TRACE)
	#define __N_OVA_BARK_TRACE
#elif __N_OVA_BARK_TRACE == 0
	#undef __N_OVA_BARK_TRACE
#endif // __N_OVA_BARK_TRACE

constexpr bool trace =
#ifdef __N_OVA_BARK_TRACE
	true
#else // !__N_OVA_BARK_TRACE
	false
#endif // __N_OVA_BARK_TRACE
;
#pragma endregion

//-----------------------------------------------------------------//
//-----------------------__N_OVA_BARK_DEBUG------------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_BARK_DEBUG

#if !defined(__N_OVA_BARK_DEBUG)
	#define __N_OVA_BARK_DEBUG
#elif __N_OVA_BARK_DEBUG == 0
	#undef __N_OVA_BARK_DEBUG
#endif // __N_OVA_BARK_DEBUG

constexpr bool debug =
#ifdef __N_OVA_BARK_DEBUG
	true
#else // !__N_OVA_BARK_DEBUG
	false
#endif // __N_OVA_BARK_DEBUG
;
#pragma endregion

//-----------------------------------------------------------------//
//-----------------------__N_OVA_BARK_ABYSS------------------------//
//-----------------------------------------------------------------//

#pragma region __N_OVA_BARK_ABYSS

#if !defined(__N_OVA_BARK_ABYSS)
	#define __N_OVA_BARK_ABYSS
#elif __N_OVA_BARK_ABYSS == 0
	#undef __N_OVA_BARK_ABYSS
#endif // __N_OVA_BARK_ABYSS

constexpr bool abyss =
#ifdef __N_OVA_BARK_ABYSS
	true
#else // !__N_OVA_BARK_ABYSS
	false
#endif // __N_OVA_BARK_ABYSS
;
#pragma endregion

} // namspace Nova::bark::def
