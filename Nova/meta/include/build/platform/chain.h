#pragma once

namespace Nova::meta::def {

	enum class ToolChain : uint8_t {
		Clang,
		GCC,
		MSVC,
	};

constexpr auto toolchain = ToolChain::
#if defined(__clang__)
	#define NOVA_TC_CLANG
	Clang
#elif defined(__GNUC__) || defined(__GNUG__)
	#define NOVA_TC_GCC
	GCC
#elif defined(_MSC_VER)
	#define NOVA_TC_MSVC
	MSVC
#else
	#define NOVA_TC_UNKNOWN
	#error Compiler Unknown!
#endif // NOVA_TC_Compiler
;

}
