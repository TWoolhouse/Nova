#pragma once
#include "def_chain.h"

#ifdef NOVA_DEBUG
#if defined(NOVA_TC_MSVC)
#define INLINE inline __forceinline
#elif defined(NOVA_TC_GCC) || defined(NOVA_TC_CLANG)
#define INLINE inline [[gnu::always_inline]]
#else
#define INLINE inline
#endif
#endif // NOVA_DEBUG

#define NODISCARD [[nodiscard]]
