#include "tpch.h"
#include <nvtl/cache.h>
#include <meta/test.h>

using namespace Nova::nvtl;

using CacheT = Nova::nvtl::CacheConstructor<size_t, size_t>;
class nvtl_CacheConstructor : public ::testing::Test {
protected:
	CacheT cache;
	// void SetUp() override {}
	// void TearDown() override {}
};
#define NOVA_TEST_CACHE(name) TEST_F(nvtl_CacheConstructor, name)

static_assert(std::derived_from<CacheT, Nova::nvtl::Cache<CacheT::key_type, CacheT::value_type>>, "Tests assume inheritance from Nova::nvtl::Cache and those base class tests pass.");

constexpr CacheT::key_type ITERATIONS = 1024;
#define ITERATE(name) (CacheT::key_type name = 0; name < ITERATIONS; ++name)

NOVA_TEST_CACHE(Get) {
	for ITERATE(i) {
		EXPECT_EQ(cache.size(), 0);
		EXPECT_NO_THROW(cache.get(i));
		// Handle should immediately be destroyed, removing the element from the cache.
		EXPECT_EQ(cache.size(), 0);
		auto item_0 = cache.get(i);
		EXPECT_EQ(cache.size(), 1);
		EXPECT_EQ(i, *item_0);

		auto item_1 = cache.get(i);
		EXPECT_EQ(cache.size(), 1);
		EXPECT_EQ(i, *item_1);
		EXPECT_EQ(item_0, item_1);
	}
}
NOVA_TEST_CACHE(Emplace) {
	EXPECT_EQ(cache.size(), 0);
	for ITERATE(i) {
		EXPECT_NO_THROW(cache.emplace(i));
	}
	EXPECT_EQ(cache.size(), 0);

	for ITERATE(i) {
		auto item = cache.emplace(i);
		EXPECT_EQ(*item, i);
	}
}
