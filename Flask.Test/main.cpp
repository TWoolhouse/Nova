#include "fpch.h"
#include <gtest/gtest.h>

TEST(SuiteName, TestName) {
	EXPECT_EQ(1, 1);
}
TEST(LOL, NICE) {
	EXPECT_EQ(2, 2);
}

int main(int argc, char const* argv[]) {
	testing::InitGoogleTest(&argc, const_cast<char**>(argv));
	return RUN_ALL_TESTS();
}
