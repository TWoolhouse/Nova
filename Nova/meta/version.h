#pragma once
#include "head.h"
#include "meta/bit.h"
#include "bark/assert.h"

#define nova_meta_version_args(Version) \
	::Nova::meta::version::major(Version), ::Nova::meta::version::minor(Version), ::Nova::meta::version::patch(Version)
#define nova_meta_version_string \
	"{}.{}.{}"

namespace Nova::meta::version {

	namespace T {
		using Major = uint16_t;
		using Minor = uint16_t;
		using Patch = uint16_t;
	} // T

	using Version = uint32_t;

	NODISCARD constexpr Version make(T::Major major, T::Minor minor, T::Patch patch) noexcept {
		nova_cassert(patch < meta::bit(12), "Patch number must be < 4096");
		nova_cassert(minor < meta::bit(10), "Patch number must be < 1024");
		nova_cassert(major < meta::bit(10), "Patch number must be < 1024");
		return
			( (major << 22)
			| (minor << 12)
			| (patch ))   ;
	}

	NODISCARD constexpr T::Major major(Version version) noexcept {
		return version >> 22;
	}
	NODISCARD constexpr T::Minor minor(Version version) noexcept {
		return (version >> 12) & 1023;
	}
	NODISCARD constexpr T::Patch patch(Version version) noexcept {
		return version & 4095;
	}

	constexpr Version engine = make(0, 1, 0);
	constexpr auto engine_name = "Nova"sv;

} // namespace Nova::meta::version
