#pragma once
#include "def_chain.h"

#define NODISCARD [[nodiscard]]

#ifdef NOVA_DEBUG
#if defined(NOVA_TC_MSVC)
#define INLINE inline __forceinline
#elif defined(NOVA_TC_GCC) || defined(NOVA_TC_CLANG)
#define INLINE inline [[gnu::always_inline]]
#else
#define INLINE inline
#endif
#else // !NOVA_DEBUG
#define INLINE inline
#endif // NOVA_DEBUG

// https://github.com/nemequ/portable-snippets/
#if defined(__has_builtin) && !defined(__ibmxl__)
#	if __has_builtin(__builtin_debugtrap)
#		define NOVA_BREAKPOINT() __builtin_debugtrap()
#	elif __has_builtin(__debugbreak)
#		define NOVA_BREAKPOINT() __debugbreak()
#	endif
#endif
#if !defined(NOVA_BREAKPOINT)
#	if defined(_MSC_VER) || defined(__INTEL_COMPILER)
#		define NOVA_BREAKPOINT() __debugbreak()
#	elif defined(__ARMCC_VERSION)
#		define NOVA_BREAKPOINT() __breakpoint(42)
#	elif defined(__ibmxl__) || defined(__xlC__)
#		include <builtins.h>
#		define NOVA_BREAKPOINT() __trap(42)
#	elif defined(__DMC__) && defined(_M_IX86)
static inline void NOVA_BREAKPOINT(void) { __asm int 3h; }
#	elif defined(__i386__) || defined(__x86_64__)
static inline void NOVA_BREAKPOINT(void) { __asm__ __volatile__("int3"); }
#	elif defined(__thumb__)
static inline void NOVA_BREAKPOINT(void) { __asm__ __volatile__(".inst 0xde01"); }
#	elif defined(__aarch64__)
static inline void NOVA_BREAKPOINT(void) { __asm__ __volatile__(".inst 0xd4200000"); }
#	elif defined(__arm__)
static inline void NOVA_BREAKPOINT(void) { __asm__ __volatile__(".inst 0xe7f001f0"); }
#	elif defined (__alpha__) && !defined(__osf__)
static inline void NOVA_BREAKPOINT(void) { __asm__ __volatile__("bpt"); }
#	elif defined(_54_)
static inline void NOVA_BREAKPOINT(void) { __asm__ __volatile__("ESTOP"); }
#	elif defined(_55_)
static inline void NOVA_BREAKPOINT(void) { __asm__ __volatile__(";\n .if (.MNEMONIC)\n ESTOP_1\n .else\n ESTOP_1()\n .endif\n NOP"); }
#	elif defined(_64P_)
static inline void NOVA_BREAKPOINT(void) { __asm__ __volatile__("SWBP 0"); }
#	elif defined(_6x_)
static inline void NOVA_BREAKPOINT(void) { __asm__ __volatile__("NOP\n .word 0x10000000"); }
#	elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ == 0) && defined(__GNUC__)
#		define NOVA_BREAKPOINT() __builtin_trap()
#	else
#		include <signal.h>
#		if defined(SIGTRAP)
#			define NOVA_BREAKPOINT() raise(SIGTRAP)
#		else
#			define NOVA_BREAKPOINT() raise(SIGABRT)
#		endif
#	endif
#endif
