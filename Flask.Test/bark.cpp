#include "tpch.h"

namespace Nova::bark { namespace {

	class Bark : public ::testing::Test {
	protected:
		void SetUp() override {
			Nova::bark::Initialize();
		}
		void TearDown() override {
			Nova::bark::Terminate();
		}
	};
	#define NOVA_TEST(name) TEST_F(Bark, name)

	// NOVA_TEST(TestName) {
	// 	EXPECT_EQ(1, 1);
	// }

}}
