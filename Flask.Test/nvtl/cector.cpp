#include "tpch.h"
#include <nvtl/cector.h>

using namespace Nova::nvtl;

using CectorT = Nova::nvtl::Cector<size_t>;
class nvtl_Cector : public ::testing::Test {
protected:
	CectorT cector{5};
	// void SetUp() override {}
	// void TearDown() override {}
};
#define NOVA_TEST_CECTOR(name) TEST_F(nvtl_Cector, name)

// TODO: Cector Testing

NOVA_TEST_CECTOR(Todo) {
	EXPECT_TRUE(false);
}
