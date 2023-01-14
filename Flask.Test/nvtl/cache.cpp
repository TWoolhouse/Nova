#include "tpch.h"
#include <nvtl/cache.h>

using namespace Nova::nvtl;

using CacheT = Nova::nvtl::Cache<size_t, size_t>;
class nvtl_Cache : public ::testing::Test {
protected:
	CacheT cache;
	// void SetUp() override {}
	// void TearDown() override {}
};
#define NOVA_TEST_CACHE(name) TEST_F(nvtl_Cache, name)

constexpr CacheT::key_type ITERATIONS = 1024;
#define ITERATE(name) (CacheT::key_type name = 0; name < ITERATIONS; ++name)

NOVA_TEST_CACHE(Empty) {
	EXPECT_EQ(cache.size(), 0) << "Cache is not empty on creation";
	
	auto item = cache.emplace(1, 10);
	EXPECT_NE(cache.size(), 0) << "Cache is empty despite creating an element";

	cache.clear();
	EXPECT_EQ(cache.size(), 0) << "Cache is not empty after clearing";
}

NOVA_TEST_CACHE(Contains) {
	for ITERATE(i) {
		EXPECT_FALSE(cache.contains(i)) << "Cache claims to contain: " << i;
	}

	{
		std::vector<CacheT::Handle> handles{ ITERATIONS };
		for ITERATE(i) {
			handles[i] = cache.emplace(i, 1);
			EXPECT_TRUE(cache.contains(i)) << "Cache does not contain: " << i;
		}

		for ITERATE(i) {
			EXPECT_TRUE(cache.contains(i)) << "Cache has lost: " << i;
		}
	}

	for ITERATE(i) {
		EXPECT_FALSE(cache.contains(i)) << "Cache still contains: " << i;
	}
}

NOVA_TEST_CACHE(Emplace) {
	for ITERATE(i) {
		EXPECT_NO_THROW(cache.emplace(i, i)) << "Unable to insert: " << i;
	}

	for ITERATE(i) {
		auto item = cache.emplace(i, i * 2);
		EXPECT_EQ(*item, i * 2) << "The correct value is not saved in the cache";
	}

	{
		std::vector<CacheT::Handle> handles{ITERATIONS};
		for ITERATE(i) {
			handles[i] = cache.emplace(i, i * 2);
		}

		for ITERATE(i) {
			EXPECT_TRUE(handles[i]) << "Handle is no longer valid: " << i;
			EXPECT_EQ(*handles[i], i * 2) << "Handles value no longer matches";
		}
	}

	EXPECT_EQ(cache.size(), 0) << "Cache should be empty!";

}

void cache_get(CacheT& cache, CacheT::Handle& item, CacheT::key_type index) {
	EXPECT_EQ(cache.get(index), item);
	EXPECT_EQ(cache[index], item);

	EXPECT_EQ(*cache.get(index), *item);
	EXPECT_EQ(*cache[index], *item);

	EXPECT_EQ(cache.get(index), cache[index]);
	EXPECT_EQ(*cache.get(index), *cache[index]);
}

NOVA_TEST_CACHE(Get) {
	for ITERATE(i) {
		EXPECT_THROW(cache.get(i), std::out_of_range) << "Get does not throw on non-existant key";
		EXPECT_THROW(cache[i], std::out_of_range) << "operator[] does not throw on non-existant key";
	}

	for ITERATE(i) {
		auto item = cache.emplace(i, i * 2);
		EXPECT_NO_THROW(cache.get(i)) << "Getting an item that is currently in the cache";
		EXPECT_NO_THROW(cache[i]) << "Getting[] an item that is currently in the cache";

		cache_get(cache, item, i);
	}

	{
		std::vector<CacheT::Handle> handles{ ITERATIONS };
		for ITERATE(i) {
			handles[i] = cache.emplace(i, i * 2);
		}
		for ITERATE(i) {
			cache_get(cache, handles[i], i);
		}
	}
}

void cache_try_get_exists(CacheT& cache, CacheT::Handle& item, CacheT::key_type index) {
	EXPECT_EQ(cache.try_get(index), item);
	EXPECT_EQ(*cache.try_get(index), *item);
}

NOVA_TEST_CACHE(TryGet) {
	for ITERATE(i) {
		EXPECT_NO_THROW(cache.try_get(i)) << "Should never throw, even on non-existant keys";
		EXPECT_FALSE(cache.try_get(i)) << "Non-existant key handle should evaluate to false";
	}

	for ITERATE(i) {
		auto item = cache.emplace(i, i * 2);
		cache_try_get_exists(cache, item, i);
	}

	{
		std::vector<CacheT::Handle> handles{ ITERATIONS };
		for ITERATE(i) {
			handles[i] = cache.emplace(i, i * 2);
		}
		for ITERATE(i) {
			cache_try_get_exists(cache, handles[i], i);
			const auto oob = i + ITERATIONS;
			EXPECT_NO_THROW(cache.try_get(oob));
			EXPECT_FALSE(cache.try_get(oob));
		}
	}
}

NOVA_TEST_CACHE(Size) {
	EXPECT_EQ(cache.size(), 0) << "Cache has a size of 0 with no elements";

	for ITERATE(i) {
		EXPECT_EQ(cache.size(), 0) << "Cache has 0 elements before emplacing";
		{
			auto item = cache.emplace(i, i * 2);
			EXPECT_EQ(cache.size(), 1) << "Cache has 1 element after emplacing";
		}
		EXPECT_EQ(cache.size(), 0) << "Cache has 0 elements after removing the only item";
	}

	{
		std::vector<CacheT::Handle> handles{ ITERATIONS };
		for ITERATE(i) {
			EXPECT_EQ(cache.size(), i);
			handles[i] = cache.emplace(i, i * 2);
			EXPECT_EQ(cache.size(), i + 1);
		}
	}

	EXPECT_EQ(cache.size(), 0) << "All elements removed from the cache";
}

NOVA_TEST_CACHE(ReferenceCount) {
	// Does the cache shrink after the reference count drops to 0
	{
		std::vector<CacheT::Handle> handles_1{ ITERATIONS };
		{
			std::vector<CacheT::Handle> handles_2{ ITERATIONS };
			for ITERATE(i) {
				handles_2[i] = cache.emplace(i, i * 2);
			}
			EXPECT_EQ(cache.size(), ITERATIONS);
			handles_1 = handles_2;
			EXPECT_EQ(cache.size(), ITERATIONS) << "Copying the handles should not change the size of the cache";
		}
		EXPECT_EQ(cache.size(), ITERATIONS) << "The handles are still active, the size should not differ.";
	}
	EXPECT_EQ(cache.size(), 0) << "The handles have been destroyed.";

}

NOVA_TEST_CACHE(ValidAfterClear) {
	// Do active handles stay valid after clearing the cache.
	for ITERATE(i) {
		auto item = cache.emplace(i, i * 2);
		cache.clear();
		EXPECT_EQ(*item, i * 2);
		EXPECT_FALSE(cache.try_get(i));
	}
}

NOVA_TEST_CACHE(Hash_Range) {
	constexpr CacheT::key_type ITERATIONS = 1024ull * 16;
	constexpr CacheT::key_type STEP = std::numeric_limits<CacheT::key_type>::max() / ITERATIONS;

	for (CacheT::key_type _i = 0, i = 0; _i < ITERATIONS; i = ++_i * STEP) {
		EXPECT_NO_THROW(cache.emplace(i, 0)) << "Inserting Item to empty Cache: " << i;
	}
	EXPECT_EQ(cache.size(), 0) << "Cache did not empty after losing all references";

	{
		std::vector<CacheT::Handle> handles{ ITERATIONS };
		cache.reserve(ITERATIONS);
		for (CacheT::key_type _i = 0, i = 0; _i < ITERATIONS; i = ++_i * STEP) {
			EXPECT_NO_THROW(handles[_i] = cache.emplace(i, 0)) << "Inserting Item to growing cache: " << i;
		}
		EXPECT_EQ(cache.size(), ITERATIONS) << "Cache does not contain the right number of items after bulk insertion";

		for (CacheT::key_type _i = 0, i = 0; _i < ITERATIONS; i = ++_i * STEP) {
			EXPECT_TRUE(cache.contains(i)) << "Cache is missing: " << i;
		}
	}

	EXPECT_EQ(cache.size(), 0) << "Cache did not empty after losing all references";
	for (CacheT::key_type _i = 0, i = 0; _i < ITERATIONS; i = ++_i * STEP) {
		EXPECT_FALSE(cache.contains(i)) << "Cache still contains: " << i;
	}

}