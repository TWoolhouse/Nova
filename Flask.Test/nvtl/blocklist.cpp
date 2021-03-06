#include "tpch.h"
#include <nvtl/blocklist.h>

namespace {
using namespace Nova::nvtl;

class nvtl_Blocklist : public ::testing::Test {
protected:
	// void SetUp() override {}
	// void TearDown() override {}
	Nova::nvtl::BlockList<int> list;
};
#define NOVA_TEST_BLOCKLIST(name) TEST_F(nvtl_Blocklist, name)

NOVA_TEST_BLOCKLIST(IteratorEmpty) {
	EXPECT_TRUE(list.empty());

	EXPECT_TRUE(list.begin() == list.end());
	EXPECT_TRUE(list.cbegin() == list.cend());
	EXPECT_TRUE(list.rbegin() == list.rend());
	// EXPECT_TRUE(list.crbegin() == list.crend());
	EXPECT_TRUE(list.blocks.begin() == list.blocks.end());
	EXPECT_TRUE(list.blocks.cbegin() == list.blocks.cend());
	EXPECT_TRUE(list.blocks.rbegin() == list.blocks.rend());
	// EXPECT_TRUE(list.blocks.crbegin() == list.blocks.crend());

	// Add Data
	list.emplace_back(1);

	EXPECT_FALSE(list.empty());

	EXPECT_TRUE(list.begin() != list.end());
	EXPECT_TRUE(list.cbegin() != list.cend());
	EXPECT_TRUE(list.rbegin() != list.rend());
	// EXPECT_TRUE(list.crbegin() != list.crend());
	EXPECT_TRUE(list.blocks.begin() != list.blocks.end());
	EXPECT_TRUE(list.blocks.cbegin() != list.blocks.cend());
	EXPECT_TRUE(list.blocks.rbegin() != list.blocks.rend());
	// EXPECT_TRUE(list.blocks.crbegin() != list.blocks.crend());
}

NOVA_TEST_BLOCKLIST(EnqueSize) {
	list.emplace_back(10);
	EXPECT_EQ(list.blocks.begin()->count, 1);
}

} // namespace
