#pragma once

#if defined(__clang__)
#define NOVA_TC_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
#define NOVA_TC_GCC
#elif defined(_MSC_VER)
#define NOVA_TC_MSVC
#else
#error Compiler Unknown!
#define NOVA_TC_UNKNOWN
#endif // NOVA_TC_Compiler
