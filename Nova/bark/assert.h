#pragma once
#include "meta/head.h"
#include "config.h"
#include "location.h"

#ifdef __N_OVA_BARK_ASSERT
#ifdef __cpp_is_consteval
#define nova_assert(cond, msg) \
do { \
	if (std::is_constant_evaluated()) { \
		::Nova::bark::assertion_constexpr(cond); \
	} else { \
		::Nova::bark::assertion(cond, msg, ::Nova::bark::Location::current()); \
	} \
} while(0)
#define nova_cassert(cond, msg) nova_assert(cond, msg)
#else
#define nova_assert(cond, msg) ::Nova::bark::assertion(cond, msg, ::Nova::bark::Location::current())
// FIXME: constexpr asserts currently not avalible
#define nova_cassert(cond, msg)
// #define nova_cassert(cond, msg) ::Nova::bark::assertion_constexpr(cond, msg, ::Nova::bark::Location::current());
#endif
#else // !__N_OVA_BARK_ASSERT
#define nova_assert(cond, msg)
#define nova_cassert(cond, msg)
#endif // __N_OVA_BARK_ASSERT

namespace Nova::bark {

	#ifdef __N_OVA_BARK_ASSERT
		NOVAPI void assertion(bool condition, const std::string_view msg, const Location location);
		NOVAPI constexpr void assertion_constexpr(bool condition, const std::string_view msg, const Location location);
	#endif // __N_OVA_BARK_ASSERT

} // namespace Nova::bark
